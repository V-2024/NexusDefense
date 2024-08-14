// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDStageManager.generated.h"

class UStageData;
class ANDStage;

UCLASS()
class NEXUSDEFENSE_API ANDStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDStageManager();

	virtual void BeginPlay() override;

	static ANDStageManager* GetInstance();

	void LoadStages(int32);
	void StartNextWave();
	bool IsStageClreared() const;
	ANDStage* GetCurrentStage() const { return CurrentStage; }
	void CreateStage(int32);

private:
	static ANDStageManager* Instance;

	UPROPERTY(EditAnywhere, Category = "Stage")
	TArray<TSoftObjectPtr<UStageData>> StageDataList;

	UPROPERTY()
	TArray<UStageData*> LoadedStages;

	UPROPERTY()
	ANDStage* CurrentStage;

	int32 CurrentStageIndex;
};
