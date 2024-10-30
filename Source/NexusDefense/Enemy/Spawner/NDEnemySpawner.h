// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/NDObjectPoolManager.h"
#include "Enemy/NDEnemy.h"
#include "NavigationSystem.h"
#include "NDEnemySpawner.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDEnemySpawner();

    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnEnemy();

    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnEnemyAtLocation(const FVector& SpawnLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UPROPERTY()
    UNDObjectPoolManager* EnemyPool;

    UPROPERTY(EditDefaultsOnly, Category = "Spawner")
    TSubclassOf<ANDEnemy> EnemyClass;

    UPROPERTY(EditDefaultsOnly, Category = "Spawner")
    int32 PoolSize = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Spawner")
    float SpawnRadius = 1000.f;

    FVector GetRandomSpawnLocation() const;

    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnInterval = 2.0f;  

    UPROPERTY(EditAnywhere, Category = "Spawner")
    bool bAutoSpawn = true;

    FTimerHandle SpawnTimerHandle;

    void StartSpawnTimer();
    void StopSpawnTimer();
};