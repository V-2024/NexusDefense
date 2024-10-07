// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDStageManager.generated.h"

class UStageData;
class ANDStage;
class UNDEventManager;
class UNDDataManager;
class UNDObjectPoolManager;
class UNDSpawnManager;

UCLASS()
class NEXUSDEFENSE_API UNDStageManager : public UObject
{
	GENERATED_BODY()
	
public:	
	UNDStageManager();


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
	UNDObjectPoolManager* ObjectPoolManager;

	UPROPERTY()
	UNDSpawnManager* SpawnManager;

	int32 CurrentStageIndex;
};
