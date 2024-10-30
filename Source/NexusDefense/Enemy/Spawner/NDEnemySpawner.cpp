// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Spawner/NDEnemySpawner.h"

// Sets default values
ANDEnemySpawner::ANDEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANDEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

    if (EnemyClass)
    {
        EnemyPool = NewObject<UNDObjectPoolManager>(this);
        if (EnemyPool)
        {
            EnemyPool->Initialize<ANDEnemy>(GetWorld(), EnemyClass, PoolSize);
            UE_LOG(LogTemp, Log, TEXT("Enemy pool initialized with size: %d"), PoolSize);

            if (bAutoSpawn)
            {
                StartSpawnTimer();
            }
        }
    }


}

void ANDEnemySpawner::SpawnEnemy()
{
    SpawnEnemyAtLocation(GetRandomSpawnLocation());
}

void ANDEnemySpawner::SpawnEnemyAtLocation(const FVector& SpawnLocation)
{
    if (!EnemyPool) return;

    if (ANDEnemy* Enemy = EnemyPool->GetPooledObject<ANDEnemy>(SpawnLocation, FRotator::ZeroRotator))
    {
        Enemy->ActivateEnemy(SpawnLocation);
        UE_LOG(LogTemp, Log, TEXT("Enemy spawned at: %s"), *SpawnLocation.ToString());
    }
}

FVector ANDEnemySpawner::GetRandomSpawnLocation() const
{
    float RandomAngle = FMath::RandRange(0.0f, 360.0f);
    FVector SpawnOffset(
        SpawnRadius * FMath::Cos(FMath::DegreesToRadians(RandomAngle)),
        SpawnRadius * FMath::Sin(FMath::DegreesToRadians(RandomAngle)),
        0.0f
    );

    FVector DesiredLocation = GetActorLocation() + SpawnOffset;

    if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld()))
    {
        FNavLocation ValidLocation;
        if (NavSystem->ProjectPointToNavigation(
            DesiredLocation,
            ValidLocation,
            FVector(500.0f, 500.0f, 500.0f)))
        {
            return ValidLocation.Location;
        }
    }

    return DesiredLocation;
}

void ANDEnemySpawner::StartSpawnTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ANDEnemySpawner::SpawnEnemy,
        SpawnInterval,
        true  // 반복 실행
    );
}

void ANDEnemySpawner::StopSpawnTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}

