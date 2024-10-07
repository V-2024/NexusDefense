#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stages/StageData.h"
#include "NDStage.generated.h"

class UNDEventManager;
class UNDDataManager;
class UNDSpawnManager;
class UNDObjectPoolManager;
class UNDScoreManager;

UCLASS()
class NEXUSDEFENSE_API ANDStage : public AActor
{
    GENERATED_BODY()

public:
    ANDStage();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void Initialize(UStageData* InStageData, UNDSpawnManager* InSpawnManager, UNDObjectPoolManager* InObjectPoolManager);
    void StartStage();
    void EndStage();
    void PauseStage();
    void ResumeStage();

    UFUNCTION(BlueprintCallable, Category = "Stage")
    void StartNextWave();

    UFUNCTION()
    void OnEnemyDefeated(AActor* DefeatedEnemy);

    UFUNCTION(BlueprintCallable, Category = "Stage")
    int32 GetCurrentWave() const { return CurrentWave; }

    UFUNCTION(BlueprintCallable, Category = "Stage")
    int32 GetTotalWaves() const { return StageData ? StageData->Waves.Num() : 0; }

    UFUNCTION(BlueprintCallable, Category = "Stage")
    int32 GetRemainingEnemies() const { return RemainingEnemies; }

    UFUNCTION(BlueprintCallable, Category = "Stage")
    bool IsStageActive() const { return bIsStageActive; }

    UFUNCTION(BlueprintCallable, Category = "Stage")
    UStageData* GetStageData() const { return StageData; }

private:
    void CheckWaveCompletion();
    void CheckStageCompletion();

    UPROPERTY()
    UStageData* StageData;

    UPROPERTY()
    UNDEventManager* EventManager;

    UPROPERTY()
    UNDDataManager* DataManager;

    UPROPERTY()
    UNDSpawnManager* SpawnManager;

    UPROPERTY()
    UNDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    UNDScoreManager* ScoreManager;

    int32 CurrentWave;
    int32 RemainingEnemies;
    bool bIsStageActive;
    float StageTimer;
};