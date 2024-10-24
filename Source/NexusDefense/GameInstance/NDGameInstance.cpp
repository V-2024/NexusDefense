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

    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;

}

void UNDGameInstance::OnStart()
{
	Super::OnStart();

	// 게임 시작 시 초기화 상태 확인
    InitializeManagers();
    SetLevelGameModes();

    // 주기적으로 초기화 상태를 확인하는 타이머 설정
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



void UNDGameInstance::SetLevelGameModes()
{
    LevelGameModes.Add("StartLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDStartLevelGameMode")));
	LevelGameModes.Add("StageSelectLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDStageSelectedGameMode")));
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
        UE_LOG(LogTemp, Warning, TEXT("UIManager address: %p"), UIManager);

        EventManager->OnStageSelected.AddUObject(UIManager, &UNDUIManager::UpdateUI);
        EventManager->OnStartLevel.AddUObject(UIManager, &UNDUIManager::StartUI);
        EventManager->OnGetPlanetInfos.BindUObject(StageManager, &UNDStageManager::GetPlanetInfos);
        EventManager->OnPlanetClicked.AddUObject(UIManager, &UNDUIManager::OnPlanetClicked);

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
        EventManager->OnStageSelected.RemoveAll(UIManager);
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

    // 모든 매니저 해제
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
		EventManager->TriggerStageSelected(CurrentGameState);
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

void UNDGameInstance::TriggerPlanetClickedEvent(int32 PlanetIndex)
{
	if (EventManager)
	{
		EventManager->TriggerPlanetClicked(PlanetIndex);
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


void UNDGameInstance::Shutdown()
{
    Super::Shutdown();

    UE_LOG(LogTemp, Warning, TEXT("GameInstance shutting down"));

    CleanupManagers();

    // 타이머 해제
    GetTimerManager().ClearAllTimersForObject(this);

    // 기타 정리 작업
    LevelGameModes.Empty();
    CurrentGameState = EGameState::Ready;
    CurrentLevelName = NAME_None;
    InitializationTimer = 0.0f;
}
