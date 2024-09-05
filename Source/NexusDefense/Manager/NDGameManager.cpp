// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDGameManager.h"


ANDGameManager* ANDGameManager::Instance = nullptr;



// Sets default values
ANDGameManager::ANDGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentGameState = EGameState::Ready;
}

ANDGameManager* ANDGameManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<ANDGameManager>();
		Instance->AddToRoot();
	}

	return Instance;
}

void ANDGameManager::BeginPlay()
{
    Super::BeginPlay();

    if (!Instance)
    {
        Instance = this;
    }
    else
    {
        Destroy();
    }
}

void ANDGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ANDGameManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    CleanupManagers();

    if (Instance)
	{
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}

    Super::EndPlay(EndPlayReason);
}


void ANDGameManager::SetGameState(EGameState NewState)
{
    CurrentGameState = NewState;
	UIManager->UpdateUI(NewState);
}

void ANDGameManager::StartGame()
{
    CurrentGameState = EGameState::Ready;

    if (UIManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("UIManager is set"));
        UIManager->UpdateUI(CurrentGameState);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("UIManager is null"));
    }
}

void ANDGameManager::PauseGame()
{
    if (CurrentGameState == EGameState::Playing)
    {
        CurrentGameState = EGameState::Paused;
        // Add Game Pause Logic
    }
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game is not playing"));
	}
}

void ANDGameManager::ResumeGame()
{
    if (CurrentGameState == EGameState::Paused)
	{
		CurrentGameState = EGameState::Playing;
		// Add Game Resume Logic
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game is not paused"));
	}

}

void ANDGameManager::EndGame()
{
    CurrentGameState = EGameState::GameOver;

    GetDataManager()->SaveGameData();
	// Add Game Over Logic

}

void ANDGameManager::SubscribeToEvents()
{
    EventManager->OnGameStarted.AddUObject(this, &ANDGameManager::HandleGameStarted);
    EventManager->OnGamePaused.AddUObject(this, &ANDGameManager::HandleGamePaused);
    EventManager->OnGameResumed.AddUObject(this, &ANDGameManager::HandleGameResumed);
    EventManager->OnGameOver.AddUObject(this, &ANDGameManager::HandleGameOver);
    //EventManager->OnStageStarted.AddUObject(this, &ANDGameManager::HandleStageStarted);
}

void ANDGameManager::UnsubscribeFromEvents()
{
	EventManager->OnGameStarted.RemoveAll(this);
	EventManager->OnGamePaused.RemoveAll(this);
	EventManager->OnGameResumed.RemoveAll(this);
	EventManager->OnGameOver.RemoveAll(this);
	//EventManager->OnStageStarted.RemoveAll(this);
}

void ANDGameManager::InitializeManagers(UWorld* World)
{
    GameWorld = World;

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

    
    //DataManager->Initialize();
    //EffectManager->Initialize(ObjectManager);
    //SoundManager->Initialize(ObjectManager);
    //ItemManager->Initialize(ObjectManager);
}

void ANDGameManager::HandleGameStarted()
{
    CurrentGameState = EGameState::Playing;

    // Add Game Start Logic
}

void ANDGameManager::HandleGamePaused()
{
    CurrentGameState = EGameState::Paused;

}

void ANDGameManager::HandleGameResumed()
{
    CurrentGameState = EGameState::Playing;

}

void ANDGameManager::HandleGameOver()
{
    CurrentGameState = EGameState::GameOver;

	GetDataManager()->SaveGameData();
}

void ANDGameManager::HandleStageStarted()
{
    // Add Stage Start Logic

}


void ANDGameManager::CleanupManagers()
{
    if (StageManager)
	{
		StageManager->Destroy();
		StageManager = nullptr;
	}

	if (SpawnManager)
	{
		SpawnManager->Destroy();
		SpawnManager = nullptr;
	}

	if (UIManager)
	{
		UIManager->Destroy();
		UIManager = nullptr;
	}

	if (ObjectManager)
	{
		ObjectManager->Destroy();
		ObjectManager = nullptr;
	}

	if (EffectManager)
	{
		EffectManager->Destroy();
		EffectManager = nullptr;
	}

	if (DataManager)
	{
		DataManager = nullptr;
	}

	if (EventManager)
	{
		EventManager = nullptr;
	}

	if (ScoreManager)
	{
		ScoreManager = nullptr;
	}

	if (SoundManager)
	{
		SoundManager = nullptr;
	}

	if (ItemManager)
	{
		ItemManager->Destroy();
		ItemManager = nullptr;
	}

    UE_LOG(LogTemp, Log, TEXT("CleanupManagers: Successfully cleaned up all managers"));

}


template<typename T>
void ANDGameManager::CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass)
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
ANDGameManager::CreateManagerInternal(TSubclassOf<T> ManagerClass)
{
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
ANDGameManager::CreateManagerInternal(TSubclassOf<T> ManagerClass)
{
    return NewObject<T>(this, ManagerClass);
}
