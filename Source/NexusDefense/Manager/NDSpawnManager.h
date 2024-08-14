// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stages/StageData.h"
#include "NDSpawnManager.generated.h"

class ANDEnemyBase;
class ANDStage;

UCLASS()
class NEXUSDEFENSE_API ANDSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDSpawnManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	static ANDSpawnManager* GetInstance();

	void SetSpawnPoint();
	void StartSpawning(ANDStage*, const FWaveInfo&);
	void StopSpawning();

private:
	void SpawnEnemy();


private:
	static ANDSpawnManager* Instance;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ANDEnemyBase> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	ANDStage* CurrentStage;

	FWaveInfo CurrentWaveInfo;
	FTimerHandle SpawnTimerHandle;
	int32 EnemiesSpawned;
	bool bIsSpawningActive;
};
