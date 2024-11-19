// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/NDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/NDManagerInterface.h"
#include "Manager/NDStageManager.h"
#include "Manager/NDUIManager.h"
#include "Manager/NDSpawnManager.h"
#include "Manager/NDEffectManager.h"
#include "Manager/NDObjectPoolManager.h"
#include "Manager/NDEventManager.h"
#include "Manager/NDDataManager.h"
#include "Manager/NDScoreManager.h"
#include "Manager/NDSoundManager.h"
#include "Enemy/NDEnemyBase.h"


UNDGameInstance::UNDGameInstance() : InitializationCheckInterval(0.1f), MaxInitializationTime(10.0f)
{
	StageManager = nullptr;
	SpawnManager = nullptr;
	UIManager = nullptr;
	ObjectManager = nullptr;
	EffectManager = nullptr;
	DataManager = nullptr;
	EventManager = nullptr;
	ScoreManager = nullptr;
	SoundManager = nullptr;
	CurrentGameState = EGameState::Ready;
	CurrentLevelName = NAME_None;
	InitializationTimer = 0.0f;
}


void UNDGameInstance::Init()
{
	Super::Init();
	InitializeGameData();
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;

}

void UNDGameInstance::OnStart()
{
	Super::OnStart();

	// ���� ���� �� �ʱ�ȭ ���� Ȯ��
    InitializeManagers();
    SetLevelGameModes();

    // �ֱ������� �ʱ�ȭ ���¸� Ȯ���ϴ� Ÿ�̸� ����
    GetTimerManager().SetTimer(InitializationTimerHandle, this, &UNDGameInstance::CheckInitialization, InitializationCheckInterval, true);
}



void UNDGameInstance::CheckInitialization()
{
    InitializationTimer += InitializationCheckInterval;

    if (AreAllManagersInitialized() && GetWorld() && GetWorld()->bIsWorldInitialized)
    {
        GetTimerManager().ClearTimer(InitializationTimerHandle);
        
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
        SoundManager;
}

void UNDGameInstance::InitializeGameData()
{
	LoadStageData();
	LoadPlanetData();
}

void UNDGameInstance::LoadStageData()
{
	// 여기서는 예시로 하드코딩된 데이터를 사용합니다.
	// 실제 구현에서는 데이터 테이블이나 JSON 파일 등에서 로드하는 것이 좋습니다.
    
	FStageInfo Stage1;
	Stage1.Name = TEXT("First Contact");
	Stage1.bIsUnlocked = true;
	Stage1.bIsCompleted = false;
	StageDataMap.Add(1, Stage1);

	FStageInfo Stage2;
	Stage2.Name = TEXT("Dark Rising");
	Stage2.bIsUnlocked = false;
	Stage2.bIsCompleted = false;
	StageDataMap.Add(2, Stage2);

	// 추가 스테이지들...
}

void UNDGameInstance::LoadPlanetData()
{
	// 예시 데이터 생성
	FPlanetInfo Earth;
	Earth.PlanetName = FName(TEXT("Earth"));
	Earth.Description = TEXT("Our home planet, the starting point of the adventure.");
	Earth.StageIDs = {1, 2};
	Earth.bIsUnlocked = true;
	Earth.Position = FVector2D(0.5f, 0.5f);
	// Earth.PlanetImage는 별도로 로드해야 함
	PlanetDataMap.Add(Earth.PlanetName, Earth);

	FPlanetInfo Mars;
	Mars.PlanetName = FName(TEXT("Mars"));
	Mars.Description = TEXT("The red planet, harboring ancient secrets.");
	Mars.StageIDs = {3, 4};
	Mars.bIsUnlocked = false;
	Mars.Position = FVector2D(0.7f, 0.3f);
	PlanetDataMap.Add(Mars.PlanetName, Mars);

	// 추가 행성들...
}


void UNDGameInstance::SetLevelGameModes()
{
    LevelGameModes.Add("StartLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDStartLevelGameMode")));
	LevelGameModes.Add("StageSelectLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDStageSelectedGameMode")));
}

void UNDGameInstance::StartGame()
{
    CurrentGameState = EGameState::Ready;

    // ���� ���� �̸� ��������
    UWorld* World = GetWorld();
    if (World)
    {
        CurrentLevelName = World->GetCurrentLevel()->GetOutermost()->GetFName();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("StartGame: World is null"));
    }

    // "StartLevel"������ Ÿ��Ʋ UI ǥ��
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
        UE_LOG(LogTemp, Warning, TEXT("UIManager address: %p"), UIManager);

        //EventManager->OnStageSelected.AddUObject(UIManager, &UNDUIManager::UpdateUI);
        EventManager->OnStartLevel.AddUObject(UIManager, &UNDUIManager::StartUI);
        //EventManager->OnGetPlanetInfos.BindUObject(StageManager, &UNDStageManager::GetPlanetInfos);
        EventManager->OnPlanetClicked.AddUObject(UIManager, &UNDUIManager::OnPlanetClicked);

        // ���ε� Ȯ��
    	/*
        if (EventManager->OnStageSelected.IsBound())
        {
            UE_LOG(LogTemp, Warning, TEXT("Successfully bound to OnStageSelected"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to bind to OnStageSelected"));
        }
        */

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
        //EventManager->OnStageSelected.RemoveAll(UIManager);
        EventManager->OnStartLevel.RemoveAll(UIManager);
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EventManager is null in UnsubscribeFromEvents"));
    }
}

void UNDGameInstance::InitializeManagers()
{
    CleanupManagers();

    CreateManager<UNDStageManager>(StageManager, UNDStageManager::StaticClass(), "StageManager");
    CreateManager<UNDSpawnManager>(SpawnManager, UNDSpawnManager::StaticClass(), "SpawnManager");
    CreateManager<UNDUIManager>(UIManager, UNDUIManager::StaticClass(), "UIManager");
    CreateManager<UNDObjectPoolManager>(ObjectManager, UNDObjectPoolManager::StaticClass(), "ObjectManager");
    CreateManager<UNDEffectManager>(EffectManager, UNDEffectManager::StaticClass(), "EffectManager");
    CreateManager<UNDDataManager>(DataManager, UNDDataManager::StaticClass(), "DataManager");
    CreateManager<UNDEventManager>(EventManager, UNDEventManager::StaticClass(), "EventManager");
    CreateManager<UNDScoreManager>(ScoreManager, UNDScoreManager::StaticClass(), "ScoreManager");
    CreateManager<UNDSoundManager>(SoundManager, UNDSoundManager::StaticClass(), "SoundManager");

    SubscribeToEvents();
}

void UNDGameInstance::CleanupManagers()
{
    if (EventManager)
	{
        UE_LOG(LogTemp, Warning, TEXT("Cleaning up subscribe"));
		UnsubscribeFromEvents();
	}

    // ��� �Ŵ��� ����
    if (StageManager) { StageManager->RemoveFromRoot(); StageManager = nullptr; }
    if (SpawnManager) { SpawnManager->RemoveFromRoot(); SpawnManager = nullptr; }
    if (UIManager) { UIManager->RemoveFromRoot(); UIManager = nullptr; }
    if (ObjectManager) { ObjectManager->RemoveFromRoot(); ObjectManager = nullptr; }
    if (EffectManager) { EffectManager->RemoveFromRoot(); EffectManager = nullptr; }
    if (DataManager) { DataManager->RemoveFromRoot();  DataManager = nullptr; }
    if (EventManager) { EventManager->RemoveFromRoot();  EventManager = nullptr; }
    if (ScoreManager) { ScoreManager->RemoveFromRoot();  ScoreManager = nullptr; }
    if (SoundManager) { SoundManager->RemoveFromRoot();  SoundManager = nullptr; }
}


void UNDGameInstance::OnLevelChanged(const FName& LevelName)
{
    

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

    if (EventManager && UIManager)
	{
		EventManager->TriggerStageSelectedMenu(CurrentGameState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerSelectStageEvent: EventManager or UIManager is null"));
	}
}

TArray<FPlanetInfo> UNDGameInstance::TriggerGetPlanetInfosEvent() const
{
    if (EventManager)
	{
		return EventManager->TriggerGetPlanetInfos();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerGetPlanetInfosEvent: EventManager is null"));
	}

	return TArray<FPlanetInfo>();
}

void UNDGameInstance::TriggerPlanetClickedEvent(const FPlanetInfo& PlanetInfo)
{
	if (EventManager)
	{
		EventManager->TriggerPlanetZoomIn(PlanetInfo);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerPlanetClickedEvent: EventManager is null"));
	}
}

void UNDGameInstance::TriggerEnemySpawn(ANDEnemyBase* Enemy) const
{
    if (EventManager)
    {
        EventManager->TriggerEnemySpawned(Enemy);
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerEnemySpawn: EventManager is null"));
    }
}

FStageInfo UNDGameInstance::GetStageInfo(int32 StageID) const
{
	if (const FStageInfo* FoundStage = StageDataMap.Find(StageID))
	{
		return *FoundStage;
	}

	// 스테이지를 찾지 못한 경우 기본 스테이지 정보 반환
	FStageInfo DefaultStage;
	DefaultStage.Name = TEXT("Unknown Stage");
	DefaultStage.bIsUnlocked = false;
	DefaultStage.bIsCompleted = false;
    
	UE_LOG(LogTemp, Warning, TEXT("Stage ID %d not found!"), StageID);
	return DefaultStage;
}

FPlanetInfo UNDGameInstance::GetPlanetInfo(const FName& PlanetName) const
{
	if (const FPlanetInfo* FoundPlanet = PlanetDataMap.Find(PlanetName))
	{
		return *FoundPlanet;
	}

	// 행성을 찾지 못한 경우 기본 행성 정보 반환
	FPlanetInfo DefaultPlanet;
	DefaultPlanet.PlanetName = FName(TEXT("Unknown Planet"));
	DefaultPlanet.Description = TEXT("Planet information not available");
	DefaultPlanet.bIsUnlocked = false;
	DefaultPlanet.Position = FVector2D::ZeroVector;
    
	UE_LOG(LogTemp, Warning, TEXT("Planet %s not found!"), *PlanetName.ToString());
	return DefaultPlanet;
}

TArray<FPlanetInfo> UNDGameInstance::GetPlanets() const
{
	TArray<FPlanetInfo> Planets;
	PlanetDataMap.GenerateValueArray(Planets);
	return Planets;
}


void UNDGameInstance::Shutdown()
{
    Super::Shutdown();

    UE_LOG(LogTemp, Warning, TEXT("GameInstance shutting down"));

    CleanupManagers();

    // Ÿ�̸� ����
    GetTimerManager().ClearAllTimersForObject(this);

    // ��Ÿ ���� �۾�
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;
}
