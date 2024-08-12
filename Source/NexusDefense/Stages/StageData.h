// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StageData.generated.h"


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
class NEXUSDEFENSE_API UStageData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
    FString StageName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
    int32 StageNumber;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
    int32 ClearScore;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
    TArray<FWaveInfo> Waves;
};
