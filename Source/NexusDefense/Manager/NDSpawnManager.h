// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stages/StageData.h"
#include "NDSpawnManager.generated.h"

class ANDEnemyBase;
class ANDStage;
class UNDEventManager;
class UNDDataManager;
class ANDObjectPoolManager;

UCLASS()
class NEXUSDEFENSE_API ANDSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDSpawnManager();

	virtual void BeginPlay() override;

	void Initialize(ANDStage*, ANDObjectPoolManager*);
	void StartSpawning(ANDStage*, const FWaveInfo&);
	void StopSpawning();

private:
	void SpawnEnemy();
	void SetupSpawnPoints();
	void ReturnEnemyToPool(ANDEnemyBase*);

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ANDEnemyBase> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	ANDStage* CurrentStage;

	UPROPERTY()
	UNDEventManager* EventManager;

	UPROPERTY()
	UNDDataManager* DataManager;

	UPROPERTY()
	ANDObjectPoolManager* ObjectPoolManager;

	FWaveInfo CurrentWaveInfo;
	FTimerHandle SpawnTimerHandle;
	int32 EnemiesSpawned;
	bool bIsSpawningActive;
};
