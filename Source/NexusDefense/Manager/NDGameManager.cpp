// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDGameManager.h"
#include "Manager/NDStageManager.h"
#include "Manager/NDUIManager.h"
#include "Manager/NDSpawnManager.h"
#include "Manager/NDEffectManager.h"
#include "Manager/NDObjectPoolManager.h"

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
        InitializeManagers();
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

void ANDGameManager::StartGame()
{
    CurrentGameState = EGameState::Playing;
    // Add Game Start Logic
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
	// Add Game Over Logic

}

void ANDGameManager::InitializeManagers()
{
    CreateManager<ANDStageManager>(StageManager, ANDStageManager::StaticClass());
    CreateManager<ANDSpawnManager>(SpawnManager, ANDSpawnManager::StaticClass());
    CreateManager<ANDUIManager>(UIManager, ANDUIManager::StaticClass());
    CreateManager<ANDObjectPoolManager>(ObjectManager, ANDObjectPoolManager::StaticClass());
    CreateManager<ANDEffectManager>(EffectManager, ANDEffectManager::StaticClass());
}

template<typename T>
void ANDGameManager::CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass)
{
    if (!ManagerPtr)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        ManagerPtr = GetWorld()->SpawnActor<T>(ManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    }
}




