// Fill out your copyright notice in the Description page of Project Settings.

#include "NDSpawnManager.h"
#include "Stages/NDStage.h"
#include "Enemy/NDEnemyBase.h"
#include "NDEventManager.h"
#include "NDDataManager.h"
#include "NDObjectPoolManager.h"
#include "Kismet/GameplayStatics.h"

// ���� ���� ���� ���� ����
// �������� ���� �ʿ�
// ��Ƽ������ ���
// ���� ���� ���� ó��
// ����� CurrentWaveInfo.SpawnPoints[0]�� ����ϵ��� �Ǿ�����


ANDSpawnManager::ANDSpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemiesSpawned = 0;
	bIsSpawningActive = false;

	EventManager = UNDEventManager::GetInstance();
	DataManager = UNDDataManager::GetInstance();
}

void ANDSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	SetupSpawnPoints();
}

void ANDSpawnManager::Initialize(ANDStage* Stage, ANDObjectPoolManager* PoolManager)
{
	CurrentStage = Stage;
	ObjectPoolManager = PoolManager;
}


void ANDSpawnManager::SetupSpawnPoints()
{
	// Find all spawn points in the level with Tag "SpawnPoint"
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "SpawnPoint", FoundActors);

	SpawnPoints = FoundActors;
}

void ANDSpawnManager::StartSpawning(ANDStage* Stage, const FWaveInfo& WaveInfo)
{
	if (SpawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No spawn points found!"));
		return;
	}

	CurrentWaveInfo = WaveInfo;
	EnemiesSpawned = 0;
	bIsSpawningActive = true;

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANDSpawnManager::SpawnEnemy, CurrentWaveInfo.SpawnInterval, true);
}

void ANDSpawnManager::StopSpawning()
{
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

	// Choose a random spawn point
	AActor* SpawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];

	// Choose an enemy type based on the current wave info
	TSubclassOf<ANDEnemyBase> EnemyTypeToSpawn = CurrentWaveInfo.SpawnPoints[0].EnemyTypes[FMath::RandRange(0, CurrentWaveInfo.SpawnPoints[0].EnemyTypes.Num() - 1)];

	// Get an enemy from the object pool
	ANDEnemyBase* SpawnedEnemy = Cast<ANDEnemyBase>(ObjectPoolManager->GetPooledObject(EnemyTypeToSpawn));

	if (SpawnedEnemy)
	{
		SpawnedEnemy->SetActorLocation(SpawnPoint->GetActorLocation());
		SpawnedEnemy->SetActorRotation(SpawnPoint->GetActorRotation());
		SpawnedEnemy->Activate();

		EnemiesSpawned++;
		EventManager->OnObjectSpawned.Broadcast(SpawnedEnemy);

		// Set up a delegate to handle enemy death
		SpawnedEnemy->OnEnemyDestroyed.AddDynamic(this, &ANDSpawnManager::ReturnEnemyToPool);
	}


	if (EnemiesSpawned >= CurrentWaveInfo.EnemyCount)
	{
		StopSpawning();
		EventManager->OnWaveComplete.Broadcast(CurrentStage->GetCurrentWave());
	}
}

void ANDSpawnManager::ReturnEnemyToPool(ANDEnemyBase* Enemy)
{
	if (Enemy)
	{
		Enemy->Deactivate();
		ObjectPoolManager->ReturnObjectToPool(Enemy);
	}
}
