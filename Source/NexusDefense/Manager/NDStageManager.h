// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDStageManager.generated.h"

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class ANDEnemyBase>> EnemyTypes;
};

UCLASS()
class NEXUSDEFENSE_API ANDStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDStageManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	static ANDStageManager* GetInstance();

	void StartStage();
	void EndStage();
	void StartNextWave();
	bool IsStageClreared() const;
	int32 GetCurrentWaveIndex() const;
	int32 GetTotalWaveCount() const;

	void OnEnemyDefeated();

	TArray<AActor*> GetSpawnPoints() const { return SpawnPoints; }

private:
	void InitializeStage();
	void CheckWaveCompletion();
	void FindSpawnPoints();

private:
	static ANDStageManager* Instance;

	UPROPERTY(EditAnywhere, Category = "Stage")
	TArray<FWaveInfo> Waves;
	TArray<AActor*> SpawnPoints;

	int32 CurrentWaveIndex;
	int32 RemainingEnemyCount;
	bool bIsStageCleared;
	bool bIsStageActive;
};
