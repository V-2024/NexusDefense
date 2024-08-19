#include "NDObjectPoolManager.h"

ANDObjectPoolManager::ANDObjectPoolManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANDObjectPoolManager::BeginPlay()
{
    Super::BeginPlay();

    for (auto ClassToPreload : PreloadClasses)
    {
        InitializePool(ClassToPreload, DefaultPoolSize);
    }
}

void ANDObjectPoolManager::InitializePool(TSubclassOf<AActor> ActorClass, int32 PoolSize)
{
    if (!ObjectPools.Contains(ActorClass))
    {
        FObjectPool NewPool;
        for (int32 i = 0; i < PoolSize; ++i)
        {
            AActor* NewObject = CreateNewObject(ActorClass);
            if (NewObject)
            {
                NewPool.PooledObjects.Add(NewObject);
            }
        }
        ObjectPools.Add(ActorClass, NewPool);
    }
}

AActor* ANDObjectPoolManager::GetPooledObject(TSubclassOf<AActor> ActorClass)
{
    if (!ObjectPools.Contains(ActorClass))
    {
        InitializePool(ActorClass, DefaultPoolSize);
    }

    FObjectPool& Pool = ObjectPools[ActorClass];

    for (AActor* PooledObject : Pool.PooledObjects)
    {
        if (PooledObject && !PooledObject->IsActorTickEnabled())
        {
            PooledObject->SetActorTickEnabled(true);
            PooledObject->SetActorHiddenInGame(false);
            PooledObject->SetActorEnableCollision(true);
            return PooledObject;
        }
    }

    // If we couldn't find an inactive object, create a new one
    AActor* NewObject = CreateNewObject(ActorClass);
    if (NewObject)
    {
        Pool.PooledObjects.Add(NewObject);
        return NewObject;
    }

    return nullptr;
}

void ANDObjectPoolManager::ReturnObjectToPool(AActor* ActorToReturn)
{
    if (ActorToReturn)
    {
        ActorToReturn->SetActorTickEnabled(false);
        ActorToReturn->SetActorHiddenInGame(true);
        ActorToReturn->SetActorEnableCollision(false);
        ActorToReturn->SetActorLocation(FVector(0, 0, -10000)); // Move it out of sight
    }
}

AActor* ANDObjectPoolManager::CreateNewObject(TSubclassOf<AActor> ActorClass)
{
    if (ActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AActor* NewObject = GetWorld()->SpawnActor<AActor>(ActorClass, FVector(0, 0, -10000), FRotator::ZeroRotator, SpawnParams);
        if (NewObject)
        {
            NewObject->SetActorTickEnabled(false);
            NewObject->SetActorHiddenInGame(true);
            NewObject->SetActorEnableCollision(false);
        }
        return NewObject;
    }
    return nullptr;
}

