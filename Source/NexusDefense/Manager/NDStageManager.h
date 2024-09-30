// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDStageManager.generated.h"

class UStageData;
class ANDStage;
class UNDEventManager;
class UNDDataManager;
class ANDObjectPoolManager;
class ANDSpawnManager;

UCLASS()
class NEXUSDEFENSE_API ANDStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDStageManager();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void StartStage(int32 StageIndex);

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void EndCurrentStage();

	UFUNCTION()
	void OnStageCleared(int32 StageIndex);

	UFUNCTION()
	void OnStageFailed(int32 StageIndex);

	void CreateStage(int32 StageIndex);

	void LoadStageData();

	bool IsStageClreared() const;

	ANDStage* GetCurrentStage() const { return CurrentStage; }

private:
	void CleanupCurrentStage();
	void SetupNextStage();

private:
	UPROPERTY(EditAnywhere, Category = "Stage")
	TArray<TSoftObjectPtr<UStageData>> StageDataList;

	UPROPERTY()
	TArray<UStageData*> LoadedStages;

	UPROPERTY()
	ANDStage* CurrentStage;

	UPROPERTY()
	UNDEventManager* EventManager;

	UPROPERTY()
	UNDDataManager* DataManager;

	UPROPERTY()
	ANDObjectPoolManager* ObjectPoolManager;

	UPROPERTY()
	ANDSpawnManager* SpawnManager;

	int32 CurrentStageIndex;
};
