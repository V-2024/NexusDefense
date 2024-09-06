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
	CurrentGameState = EGameState::Ready;

    // 에디터 키자마자 팅김
    //InitializeManagers();
    // 에디터 키자마자 팅김
    //ChangeGameModeForLevel("StartLevel");
}

void UNDGameInstance::Init()
{
	Super::Init();

	// Add all the game modes for the levels
    LevelGameModes.Add("StartLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDGameMode")));
    LevelGameModes.Add("EnemyTestLevel", TSoftClassPtr<AGameModeBase>(FSoftClassPath("/Script/NexusDefense.NDInStageGameMode")));

    // Store the Managers in the GameInstance
    /*if (!StageManager)
	{
		StageManager = NewObject<ANDStageManager>(this, ANDStageManager::StaticClass());
	}

    if (!SpawnManager)
	{
		SpawnManager = NewObject<ANDSpawnManager>(this, ANDSpawnManager::StaticClass());
	}

    if (!UIManager)
	{
		UIManager = NewObject<ANDUIManager>(this, ANDUIManager::StaticClass());
	}

    if (!ObjectManager)
	{
		ObjectManager = NewObject<ANDObjectPoolManager>(this, ANDObjectPoolManager::StaticClass());
	}

    if (!EffectManager)
	{
		EffectManager = NewObject<ANDEffectManager>(this, ANDEffectManager::StaticClass());
	}

    if (!DataManager)
	{
		DataManager = NewObject<UNDDataManager>(this, UNDDataManager::StaticClass());
	}

    if (!EventManager)
	{
		EventManager = NewObject<UNDEventManager>(this, UNDEventManager::StaticClass());
	}

    if (!ScoreManager)
	{
		ScoreManager = NewObject<UNDScoreManager>(this, UNDScoreManager::StaticClass());
	}

	if (!SoundManager)
	{
		SoundManager = NewObject<UNDSoundManager>(this, UNDSoundManager::StaticClass());
	}

	if (!ItemManager)
	{
		ItemManager = NewObject<ANDItemManager>(this, ANDItemManager::StaticClass());
	}*/
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
    CreateManager<ANDStageManager>(StageManager, ANDStageManager::StaticClass());
    CreateManager<ANDSpawnManager>(SpawnManager, ANDSpawnManager::StaticClass());
    CreateManager<ANDUIManager>(UIManager, ANDUIManager::StaticClass());
    CreateManager<ANDObjectPoolManager>(ObjectManager, ANDObjectPoolManager::StaticClass());
    CreateManager<ANDEffectManager>(EffectManager, ANDEffectManager::StaticClass());
    CreateManager<UNDDataManager>(DataManager, UNDDataManager::StaticClass());
    CreateManager<UNDEventManager>(EventManager, UNDEventManager::StaticClass());
    CreateManager<UNDScoreManager>(ScoreManager, UNDScoreManager::StaticClass());
    CreateManager<UNDSoundManager>(SoundManager, UNDSoundManager::StaticClass());
    CreateManager<ANDItemManager>(ItemManager, ANDItemManager::StaticClass());
}

void UNDGameInstance::OnLevelChanged(const FName& LevelName)
{
    

}

template<typename T>
void UNDGameInstance::CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass)
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

    ManagerPtr = CreateManagerInternal<T>(ManagerClass);

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
UNDGameInstance::CreateManagerInternal(TSubclassOf<T> ManagerClass)
{
    UWorld* GameWorld = GetWorld();

    if (!GameWorld)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateManagerInternal: World is null"));
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GameWorld->SpawnActor<T>(ManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}


template<typename T>
typename std::enable_if<!std::is_base_of<AActor, T>::value, T*>::type
UNDGameInstance::CreateManagerInternal(TSubclassOf<T> ManagerClass)
{
    return NewObject<T>(this, ManagerClass);
}
