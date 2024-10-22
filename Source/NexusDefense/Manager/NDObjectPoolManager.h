// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDObjectPoolManager.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDObjectPoolManager : public UObject
{
    GENERATED_BODY()

public:
    UNDObjectPoolManager();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void CreatePool(UWorld* WorldContext, TSubclassOf<AActor> ActorToSpawn, int32 PoolSize);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    AActor* GetPooledObject(const FVector& Position, const FRotator& Rotation);

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void ReturnToPool(AActor* ActorToReturn);

private:
    UPROPERTY()
    TArray<AActor*> PooledObjects;

    UPROPERTY()
    TSubclassOf<AActor> PooledObjectClass;

    UPROPERTY()
    UWorld* World;

private:
    AActor* CreateNewObject(const FVector& Position, const FRotator& Rotation);
};
