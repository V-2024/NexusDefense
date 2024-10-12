// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Stages/StageData.h"
#include "NDSpawnManager.generated.h"

class ANDEnemyBase;
class ANDStage;
class UNDGameInstance;

UCLASS()
class NEXUSDEFENSE_API UNDSpawnManager : public UObject
{
	GENERATED_BODY()
	
public:	
	UNDSpawnManager();

	virtual void PostLoad() override;

	void Initialize(ANDStage*);
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
	UNDGameInstance* GameInstance;

	FWaveInfo CurrentWaveInfo;
	FTimerHandle SpawnTimerHandle;
	int32 EnemiesSpawned;
	bool bIsSpawningActive;
};
