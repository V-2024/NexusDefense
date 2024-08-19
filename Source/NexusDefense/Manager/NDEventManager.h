// NDEventManager.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDEventManager.generated.h"

class ANDEnemyBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectSpawned, AActor*, SpawnedObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroyed, AActor*, DestroyedObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStart, int32, WaveNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveComplete, int32, WaveNumber);


UCLASS()
class NEXUSDEFENSE_API UNDEventManager : public UObject
{
    GENERATED_BODY()

public:
    static UNDEventManager* GetInstance();

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStageStart OnStageStart;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStageEnd OnStageEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStageCompleted OnStageCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGameOver OnGameOver;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnWaveStart OnWaveStart;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnWaveComplete OnWaveComplete;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnObjectSpawned OnObjectSpawned;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnObjectDestroyed OnObjectDestroyed;


private:
    static UNDEventManager* Instance;
};
