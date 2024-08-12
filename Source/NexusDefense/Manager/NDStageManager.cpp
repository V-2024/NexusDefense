// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDStageManager.h"
#include "Manager/NDGameManager.h"
#include "Manager/NDSpawnManager.h"
#include "Kismet/GameplayStatics.h"


ANDStageManager::ANDStageManager()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentWaveIndex = 0;
	RemainingEnemyCount = 0;
	bIsStageCleared = false;
	bIsStageActive = false;
}


void ANDStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	if(!Instance)
	{
		Instance = this;
		InitializeStage();
	}
	else
	{
		Destroy();
	}
}


void ANDStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsStageCleared)
	{
		// Add Stage Clear Logic
	}
}

ANDStageManager* ANDStageManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<ANDStageManager>();
		Instance->AddToRoot();
	}

	return Instance;
}

void ANDStageManager::StartStage()
{
	bIsStageActive = true;
	StartNextWave();
}

void ANDStageManager::EndStage()
{
	bIsStageActive = false;
	// Add Stage End Logic, get Reward and move to main menu
}

void ANDStageManager::StartNextWave()
{
	if (CurrentWaveIndex < Waves.Num())
	{
		RemainingEnemyCount = Waves[CurrentWaveIndex].EnemyCount;
		// SpawnManager를 통해 적 스폰 시작
		ANDSpawnManager* SpawnManager = ANDGameManager::GetInstance()->GetSpawnManager();
		if (SpawnManager)
		{
			SpawnManager->StartSpawning(Waves[CurrentWaveIndex]);
		}
	}
	else
	{
		EndStage();
	}
}

bool ANDStageManager::IsStageClreared() const
{
	return CurrentWaveIndex >= Waves.Num() && RemainingEnemyCount == 0;
}

int32 ANDStageManager::GetCurrentWaveIndex() const
{
	return CurrentWaveIndex;
}

int32 ANDStageManager::GetTotalWaveCount() const
{
	return Waves.Num();
}

void ANDStageManager::OnEnemyDefeated()
{
	RemainingEnemyCount--;

	if (RemainingEnemyCount <= 0)
	{
		CheckWaveCompletion();
	}
}

void ANDStageManager::InitializeStage()
{
	// Initialize Waves, Enemy Types, Spawn Intervals

}

void ANDStageManager::CheckWaveCompletion()
{
	CurrentWaveIndex++;
	if (CurrentWaveIndex < Waves.Num())
	{
		StartNextWave();
	}
	else
	{
		EndStage();
	}
}

void ANDStageManager::FindSpawnPoints()
{
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("SpawnPoint"))
		{
			SpawnPoints.Add(*ActorItr);
		}
	}
}



