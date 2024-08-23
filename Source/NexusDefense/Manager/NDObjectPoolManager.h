// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDObjectPoolManager.generated.h"

class ANDObjectPoolManager;
class UAudioComponent;
class UParticleSystemComponent;

USTRUCT()
struct FObjectPool
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<AActor*> PooledObjects;
};

UCLASS()
class NEXUSDEFENSE_API ANDObjectPoolManager : public AActor
{
    GENERATED_BODY()

public:
    ANDObjectPoolManager();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    AActor* GetPooledObject(TSubclassOf<AActor> ActorClass);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void ReturnObjectToPool(AActor* ReturnObject);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void ReturnParticleToPool(UParticleSystemComponent* ReturnParticle);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void ReturnSoundToPool(UAudioComponent* ReturnSound);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void InitializePool(TSubclassOf<AActor> ActorClass, int32 PoolSize);

private:
    AActor* CreateNewObject(TSubclassOf<AActor>);

    UPROPERTY()
    TMap<TSubclassOf<AActor>, FObjectPool> ObjectPools;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    int32 DefaultPoolSize = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    TArray<TSubclassOf<AActor>> PreloadClasses;
};
