// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/NDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/NDStageManager.h"
#include "Manager/NDUIManager.h"
#include "Manager/NDSpawnManager.h"
#include "Manager/NDEffectManager.h"
#include "Manager/NDObjectPoolManager.h"
#include "Manager/NDEventManager.h"
#include "Manager/NDDataManager.h"
#include "Manager/NDScoreManager.h"
#include "Manager/NDSoundManager.h"
#include "Manager/NDItemManager.h"


UNDGameInstance::UNDGameInstance()
{
    
}

void UNDGameInstance::Init()
{
	Super::Init();

    StageManager = nullptr;
    SpawnManager = nullptr;
    UIManager = nullptr;
    ObjectManager = nullptr;
    EffectManager = nullptr;
    DataManager = nullptr;
    EventManager = nullptr;
    ScoreManager = nullptr;
    SoundManager = nullptr;
    ItemManager = nullptr;

    PlanetInfos.Empty();
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;

    InitializeManagers();
    SetLevelGameModes();
    InitializePlanetInfos();

    // 주기적으로 초기화 상태를 확인하는 타이머 설정
    GetTimerManager().SetTimer(InitializationTimerHandle, this, &UNDGameInstance::CheckInitialization, InitializationCheckInterval, true);
}



void UNDGameInstance::CheckInitialization()
{
    InitializationTimer += InitializationCheckInterval;

    if (AreAllManagersInitialized() && GetWorld() && GetWorld()->bIsWorldInitialized)
    {
        GetTimerManager().ClearTimer(InitializationTimerHandle);
        SubscribeToEvents();
        StartGame();
    }
    else if (InitializationTimer >= MaxInitializationTime)
    {
        GetTimerManager().ClearTimer(InitializationTimerHandle);
        UE_LOG(LogTemp, Warning, TEXT("Initialization timed out. Starting game anyway."));
        StartGame();
    }
}

bool UNDGameInstance::AreAllManagersInitialized()
{
    // Check if all managers are initialized
    return StageManager && SpawnManager && UIManager && ObjectManager &&
        EffectManager && DataManager && EventManager && ScoreManager &&
        SoundManager && ItemManager;
}

void UNDGameInstance::InitializePlanetInfos()
{
    // Initialized the planet information
    // In practice, we need to load from a datatable or external file
    FPlanetInfo Planet1;
    Planet1.PlanetName = TEXT("Terra Prime");
    Planet1.Description = TEXT("A lush, Earth-like planet teeming with life.");
    Planet1.bIsUnlocked = true;
    Planet1.Position = FVector2D(100, 100);
    Planet1.StageIDs = { 1, 2, 3 };
    PlanetInfos.Add(Planet1);

    FPlanetInfo Planet2;
    Planet2.PlanetName = TEXT("Frozen Helios");
    Planet2.Description = TEXT("An icy world with hidden resources beneath its surface.");
    Planet2.bIsUnlocked = false;
    Planet2.Position = FVector2D(300, 200);
    Planet2.StageIDs = { 4, 5, 6 };
    PlanetInfos.Add(Planet2);

    // more planets...
}

void UNDGameInstance::SetLevelGameModes()
{
    LevelGameModes.Add("StartLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDStartLevelGameMode")));
	LevelGameModes.Add("StageSelectLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDInStageGameMode")));
}

void UNDGameInstance::StartGame()
{
    CurrentGameState = EGameState::Ready;

    // 현재 레벨 이름 가져오기
    UWorld* World = GetWorld();
    if (World)
    {
        CurrentLevelName = World->GetCurrentLevel()->GetOutermost()->GetFName();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("StartGame: World is null"));
    }

    // "StartLevel"에서만 타이틀 UI 표시
    if (CurrentLevelName == "/Game/NexusDefense/Maps/UEDPIE_0_StartLevel" && UIManager)
    {
        UE_LOG(LogTemp, Log, TEXT("StartGame: Showing main menu"));

        TriggerGameStartedEvent();
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("StartGame: Starting game"));
    }
}


void UNDGameInstance::ChangeGameModeForLevel(const FName& LevelName)
{
    if (TSoftClassPtr<AGameModeBase>* GameModeClassPtr = LevelGameModes.Find(LevelName))
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FString Options = "";
            UGameplayStatics::OpenLevel(World, LevelName, true, Options + "?game=" + GameModeClassPtr->ToString());

            UE_LOG(LogTemp, Log, TEXT("ChangeGameModeForLevel: Changed game mode for level %s"), *LevelName.ToString());
        }
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ChangeGameModeForLevel: World is null"));
		}
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("ChangeGameModeForLevel: GameMode not found for level %s"), *LevelName.ToString());
	}
}

void UNDGameInstance::SetGameState(EGameState NewState)
{
	CurrentGameState = NewState;
}

void UNDGameInstance::SubscribeToEvents()
{
    if (EventManager && UIManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Subscribing to events"));
        EventManager->OnStageSelected.AddUObject(UIManager, &ANDUIManager::UpdateUI);
        EventManager->OnStartLevel.AddUObject(UIManager, &ANDUIManager::StartUI);

        // 바인딩 확인
        if (EventManager->OnStageSelected.IsBound())
        {
            UE_LOG(LogTemp, Warning, TEXT("Successfully bound to OnStageSelected"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to bind to OnStageSelected"));
        }

        if(EventManager->OnStartLevel.IsBound())
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully bound to OnStartLevel"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to bind to OnStartLevel"));
		}
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EventManager or UIManager is null in SubscribeToEvents"));
    }
}

void UNDGameInstance::UnsubscribeFromEvents()
{
	if (EventManager)
	{
        EventManager->OnStageSelected.Clear();
        EventManager->OnStartLevel.Clear();
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EventManager is null in UnsubscribeFromEvents"));
    }
}

void UNDGameInstance::InitializeManagers()
{
    if (EventManager) EventManager->ConditionalBeginDestroy();
    if (UIManager) UIManager->ConditionalBeginDestroy();
    if (StageManager) StageManager->ConditionalBeginDestroy();
    if (SpawnManager) SpawnManager->ConditionalBeginDestroy();
    if (ObjectManager) ObjectManager->ConditionalBeginDestroy();
    if (EffectManager) EffectManager->ConditionalBeginDestroy();
    if (DataManager) DataManager->ConditionalBeginDestroy();
    if (ScoreManager) ScoreManager->ConditionalBeginDestroy();
    if (SoundManager) SoundManager->ConditionalBeginDestroy();
    if (ItemManager) ItemManager->ConditionalBeginDestroy();

    CreateManager<ANDStageManager>(StageManager, ANDStageManager::StaticClass(), "StageManager");
    CreateManager<ANDSpawnManager>(SpawnManager, ANDSpawnManager::StaticClass(), "SpawnManager");
    CreateManager<ANDUIManager>(UIManager, ANDUIManager::StaticClass(), "UIManager");
    CreateManager<ANDObjectPoolManager>(ObjectManager, ANDObjectPoolManager::StaticClass(), "ObjectManager");
    CreateManager<ANDEffectManager>(EffectManager, ANDEffectManager::StaticClass(), "EffectManager");
    CreateManager<UNDDataManager>(DataManager, UNDDataManager::StaticClass(), "DataManager");
    CreateManager<UNDEventManager>(EventManager, UNDEventManager::StaticClass(), "EventManager");
    CreateManager<UNDScoreManager>(ScoreManager, UNDScoreManager::StaticClass(), "ScoreManager");
    CreateManager<UNDSoundManager>(SoundManager, UNDSoundManager::StaticClass(), "SoundManager");
    CreateManager<ANDItemManager>(ItemManager, ANDItemManager::StaticClass(), "ItemManager");
}

void UNDGameInstance::CleanupManagers()
{
    if (EventManager)
	{
		UnsubscribeFromEvents();
	}

	if (StageManager) StageManager->ConditionalBeginDestroy();
	if (SpawnManager) SpawnManager->ConditionalBeginDestroy();
	if (UIManager) UIManager->ConditionalBeginDestroy();
	if (ObjectManager) ObjectManager->ConditionalBeginDestroy();
	if (EffectManager) EffectManager->ConditionalBeginDestroy();
	if (DataManager) DataManager->ConditionalBeginDestroy();
	if (EventManager) EventManager->ConditionalBeginDestroy();
	if (ScoreManager) ScoreManager->ConditionalBeginDestroy();
	if (SoundManager) SoundManager->ConditionalBeginDestroy();
	if (ItemManager) ItemManager->ConditionalBeginDestroy();
}

void UNDGameInstance::CleanupOnGameEnd()
{
    CleanupManagers();

    // 타이머 해제
    GetTimerManager().ClearAllTimersForObject(this);

    // 모든 매니저 해제
    StageManager = nullptr;
    SpawnManager = nullptr;
    UIManager = nullptr;
    ObjectManager = nullptr;
    EffectManager = nullptr;
    DataManager = nullptr;
    EventManager = nullptr;
    ScoreManager = nullptr;
    SoundManager = nullptr;
    ItemManager = nullptr;

    // 기타 정리 작업
    PlanetInfos.Empty();
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;
}

void UNDGameInstance::OnLevelChanged(const FName& LevelName)
{
    

}

TArray<FPlanetInfo> UNDGameInstance::GetPlanetInfos() const
{
    return PlanetInfos;
}

bool UNDGameInstance::IsPlanetUnlocked(int32 PlanetIndex) const
{
    if (PlanetInfos.IsValidIndex(PlanetIndex))
    {
        return PlanetInfos[PlanetIndex].bIsUnlocked;
    }

    return false;
}

void UNDGameInstance::TriggerGameStartedEvent()
{
    if (EventManager)
	{
		EventManager->TriggerStartLevel();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerGameStartedEvent: EventManager is null"));
	}
}

void UNDGameInstance::TriggerSelectStageEvent()
{
    SetGameState(EGameState::StageSelect);

    if (EventManager)
	{
		EventManager->TriggerStageSelected(CurrentGameState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerSelectStageEvent: EventManager is null"));
	}
}

template<typename T>
void UNDGameInstance::CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass, FName ManagerName)
{
    if (!ManagerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateManager: ManagerClass is null for %s"), *T::StaticClass()->GetName());
        return;
    }

    if (ManagerPtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateManager: Manager already exists for %s"), *T::StaticClass()->GetName());
        return;
    }

    ManagerPtr = CreateManagerInternal<T>(ManagerClass, ManagerName);

    if (ManagerPtr)
    {
        UE_LOG(LogTemp, Log, TEXT("CreateManager: Successfully created manager of class %s"), *ManagerClass->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CreateManager: Failed to create manager of class %s"), *ManagerClass->GetName());
    }
}

template<typename T>
typename std::enable_if<std::is_base_of<AActor, T>::value, T*>::type
UNDGameInstance::CreateManagerInternal(TSubclassOf<T> ManagerClass, FName ManagerName)
{
    UWorld* GameWorld = GetWorld();
    if (!GameWorld)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateManagerInternal: World is null"));
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    if (ManagerName != NAME_None)
    {
        SpawnParams.Name = ManagerName;
    }

    return GameWorld->SpawnActor<T>(ManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}

template<typename T>
typename std::enable_if<!std::is_base_of<AActor, T>::value, T*>::type
UNDGameInstance::CreateManagerInternal(TSubclassOf<T> ManagerClass, FName ManagerName)
{
    return NewObject<T>(this, ManagerClass, ManagerName);
}

void UNDGameInstance::Shutdown()
{
    Super::Shutdown();

    // 타이머 해제
    GetTimerManager().ClearAllTimersForObject(this);

    // 모든 매니저 해제
    StageManager = nullptr;
    SpawnManager = nullptr;
    UIManager = nullptr;
    ObjectManager = nullptr;
    EffectManager = nullptr;
    DataManager = nullptr;
    EventManager = nullptr;
    ScoreManager = nullptr;
    SoundManager = nullptr;
    ItemManager = nullptr;

    // 기타 정리 작업
    PlanetInfos.Empty();
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;
}
