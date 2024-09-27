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
    StageManager        = nullptr;
    SpawnManager        = nullptr;
    UIManager           = nullptr;
    ObjectManager       = nullptr;
    EffectManager       = nullptr;
    DataManager         = nullptr;
    EventManager        = nullptr;
    ScoreManager        = nullptr;
    SoundManager        = nullptr;
    ItemManager         = nullptr;
}

void UNDGameInstance::Init()
{
	Super::Init();

    // Add all the game modes for the levels
    LevelGameModes.Add("StartLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDGameMode")));
    LevelGameModes.Add("EnemyTestLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDInStageGameMode")));

    InitializeManagers();

    // 주기적으로 초기화 상태를 확인하는 타이머 설정
    GetTimerManager().SetTimer(InitializationTimerHandle, this, &UNDGameInstance::CheckInitialization, InitializationCheckInterval, true);

    //ChangeGameModeForLevel("StartLevel");
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
        SoundManager && ItemManager;
}

void UNDGameInstance::StartGame()
{
    CurrentGameState = EGameState::Ready;

    if (UIManager)
	{
		UIManager->StartUI();
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
        }
    }
}

void UNDGameInstance::SetGameState(EGameState NewState)
{
	CurrentGameState = NewState;
}

void UNDGameInstance::SubscribeToEvents()
{
	if (EventManager)
	{
        //EventManager->OnGameLevelChanged.AddUObject(this, &UNDGameInstance::OnLevelChanged);
	}
}

void UNDGameInstance::UnsubscribeFromEvents()
{
	if (EventManager)
	{
		EventManager->UnsubscribeFromEvents();
	}
}

void UNDGameInstance::InitializeManagers()
{
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

void UNDGameInstance::OnLevelChanged(const FName& LevelName)
{
    

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
