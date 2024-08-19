// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageData.h"
#include "NDStage.generated.h"

class UNDEventManager;
class UNDDataManager;

UCLASS()
class NEXUSDEFENSE_API ANDStage : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDStage();

    virtual void BeginPlay() override;
    void Initialize(UStageData* InStageData);
    void StartStage();
    void EndStage();
    bool IsStageCleared() const;
    void StartNextWave();

    int32 GetCurrentWave() const { return CurrentWave; }
    int32 GetTotalWaves() const { return StageData ? StageData->Waves.Num() : 0; }
    int32 GetClearScore() const { return StageData ? StageData->ClearScore : 0; }

    UFUNCTION()
    void OnEnemyDefeated();


private:
    void CheckWaveCompletion();


public:
    UPROPERTY()
    UStageData* StageData;

    int32 CurrentWave;
    int32 RemainingEnemies;
    bool bIsStageActive;

    UPROPERTY()
    UNDEventManager* EventManager;

    UPROPERTY()
    UNDDataManager* DataManager;
};
