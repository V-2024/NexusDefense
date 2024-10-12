// Fill out your copyright notice in the Description page of Project Settings.

#include "NDSpawnManager.h"
#include "Stages/NDStage.h"
#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/NDGameInstance.h"

// 기존 랜덤 스폰 로직 수정
// 스폰간격 조절 필요
// 멀티스레딩 고려
// 스폰 실패 예외 처리
// 현재는 CurrentWaveInfo.SpawnPoints[0]만 사용하도록 되어있음


UNDSpawnManager::UNDSpawnManager() : EnemiesSpawned(0), bIsSpawningActive(false)
{

}

void UNDSpawnManager::PostLoad()
{
	Super::PostLoad();

	SetupSpawnPoints();

	//GameInstance = Cast<UNDGameInstance>(GetGameInstance());
}


void UNDSpawnManager::Initialize(ANDStage* Stage)
{
	CurrentStage = Stage;
}


void UNDSpawnManager::SetupSpawnPoints()
{
	// Find all spawn points in the level with Tag "SpawnPoint"
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "SpawnPoint", FoundActors);

	SpawnPoints = FoundActors;
}

void UNDSpawnManager::StartSpawning(ANDStage* Stage, const FWaveInfo& WaveInfo)
{
	if (SpawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No spawn points found!"));
		return;
	}

	CurrentWaveInfo = WaveInfo;
	EnemiesSpawned = 0;
	bIsSpawningActive = true;

	//GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &UNDSpawnManager::SpawnEnemy, CurrentWaveInfo.SpawnInterval, true);
}

void UNDSpawnManager::StopSpawning()
{
	bIsSpawningActive = false;
	//GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void UNDSpawnManager::SpawnEnemy()
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
	ANDEnemyBase* SpawnedEnemy = Cast<ANDEnemyBase>(GameInstance->EnemySpawned(EnemyTypeToSpawn));


	if (SpawnedEnemy)
	{
		SpawnedEnemy->SetActorLocation(SpawnPoint->GetActorLocation());
		SpawnedEnemy->SetActorRotation(SpawnPoint->GetActorRotation());
		SpawnedEnemy->Activate();

		EnemiesSpawned++;
		//EventManager->OnObjectSpawned.Broadcast(SpawnedEnemy);

		// Set up a delegate to handle enemy death
		//SpawnedEnemy->OnEnemyDestroyed.AddDynamic(this, &ANDSpawnManager::ReturnEnemyToPool);
		GameInstance->TriggerEnemySpawn(SpawnedEnemy);
	}


	if (EnemiesSpawned >= CurrentWaveInfo.EnemyCount)
	{
		StopSpawning();
		//EventManager->OnWaveComplete.Broadcast(CurrentStage->GetCurrentWave());
	}
}

void UNDSpawnManager::ReturnEnemyToPool(ANDEnemyBase* Enemy)
{
	if (Enemy)
	{
		Enemy->Deactivate();
		//ObjectPoolManager->ReturnObjectToPool(Enemy);
	}
}
