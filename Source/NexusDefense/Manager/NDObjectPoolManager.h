// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDObjectPoolManager.generated.h"

class UAudioComponent;
class UParticleSystemComponent;

USTRUCT()
struct FObjectPoolData
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<AActor*> ActiveObjects;

    UPROPERTY()
	TArray<AActor*> InactiveObjects;

	int32 PoolSize = 0;
};


UCLASS()
class NEXUSDEFENSE_API UNDObjectPoolManager : public UObject
{
    GENERATED_BODY()

public:
    UNDObjectPoolManager();

    void InitializePool(TSubclassOf<AActor> ActorClass, int32 PoolSize);
	
    AActor* GetPooledObject(TSubclassOf<AActor> ActorClass);
    void ReturnObjectToPool(AActor* ReturnObject);

    void CleanupPool();

private:
    AActor* CreateNewObject(TSubclassOf<AActor>);
    void ExpandPool(TSubclassOf<AActor> ActorClass, int32 AdditionalSize);


private:
    UPROPERTY()
    TMap<TSubclassOf<AActor>, FObjectPoolData> ObjectPools;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    int32 DefaultPoolSize = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    TArray<TSubclassOf<AActor>> PreloadClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	float PoolExpansionFactor = 1.5f;
};
