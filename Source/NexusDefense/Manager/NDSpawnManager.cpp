// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDSpawnManager.h"

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
		FindSpawnPoints();
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

void ANDSpawnManager::StartSpawning(const FWaveInfo& WaveInfo)
{
	if (SpawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Spawn Points Found"));
		return;
	}


	if (bIsSpawningActive)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning Already Active"));
		return;
	}

	bIsSpawningActive = true;
	CurrentWaveInfo = WaveInfo;
	RemainingEnemyCount = CurrentWaveInfo.EnemyCount;
	CurrentWaveIndex = ANDStageManager::GetInstance()->GetCurrentWaveIndex();
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

	
}

void ANDSpawnManager::GetSpawnPoint()
{
	SpawnPoints = ANDStageManager::GetInstance()->GetSpawnPoints();
}

