// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDGameManager.h"
#include "Manager/NDSpawnManager.h"
#include "Stages/NDStage.h"
#include "Enemy/NDEnemyBase.h"
#include "EngineUtils.h"

ANDSpawnManager* ANDSpawnManager::Instance = nullptr;

// Sets default values
ANDSpawnManager::ANDSpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemiesSpawned = 0;
	bIsSpawningActive = false;
}

void ANDSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Instance)
	{
		Instance = this;
		GetSpawnPoint();
	}
	else
	{
		Destroy();
	}
}

// Called every frame
void ANDSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ANDSpawnManager* ANDSpawnManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<ANDSpawnManager>();
		Instance->AddToRoot();
	}

	return Instance;
}

void ANDSpawnManager::StartSpawning(ANDStage* Stage, const FWaveInfo& WaveInfo)
{
	if (SpawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No spawn points found!"));
		return;
	}

	CurrentStage = Stage;
	CurrentWaveInfo = WaveInfo;
	EnemiesSpawned = 0;
	bIsSpawningActive = true;

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANDSpawnManager::SpawnEnemy, CurrentWaveInfo.SpawnInterval, true);
}

void ANDSpawnManager::StopSpawning()
{
	if (!bIsSpawningActive)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning is not active"));
		return;
	}

	bIsSpawningActive = false;
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void ANDSpawnManager::SpawnEnemy()
{
	if (!bIsSpawningActive || EnemiesSpawned >= CurrentWaveInfo.EnemyCount)
	{
		StopSpawning();
		return;
	}

	// Spawn enemy
}

void ANDSpawnManager::GetSpawnPoint()
{
	SpawnPoints = CurrentStage->GetSpawnPoints();
}

