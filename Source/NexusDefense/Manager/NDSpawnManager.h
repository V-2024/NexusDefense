// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/NDStageManager.h"
#include "NDSpawnManager.generated.h"

class ANDEnemyBase;

UCLASS()
class NEXUSDEFENSE_API ANDSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDSpawnManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	static ANDSpawnManager* GetInstance();

	void StartSpawning(const FWaveInfo& WaveInfo);
	void StopSpawning();

private:
	void SpawnEnemy();
	void GetSpawnPoint();


private:
	static ANDSpawnManager* Instance;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ANDEnemyBase> EnemyClass;

	FWaveInfo CurrentWaveInfo;
	FTimerHandle SpawnTimerHandle;
	int32 EnemiesSpawned;
	int32 CurrentWaveIndex;
	int32 RemainingEnemyCount;
	bool bIsSpawningActive;

};
