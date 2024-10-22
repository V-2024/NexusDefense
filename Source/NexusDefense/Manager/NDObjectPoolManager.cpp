#include "NDObjectPoolManager.h"

UNDObjectPoolManager::UNDObjectPoolManager()
{
    UE_LOG(LogTemp, Warning, TEXT("UObjectPoolManager Constructor Called"));
}

void UNDObjectPoolManager::BeginDestroy()
{
    UE_LOG(LogTemp, Warning, TEXT("UObjectPoolManager BeginDestroy Called"));
    Super::BeginDestroy();
}



void UNDObjectPoolManager::CreatePool(UWorld* WorldContext, TSubclassOf<AActor> ActorToSpawn, int32 PoolSize)
{
    World = WorldContext;
    PooledObjectClass = ActorToSpawn;

    if (!World || !PooledObjectClass) return;

    for (int32 i = 0; i < PoolSize; i++)
    {
        AActor* NewObject = CreateNewObject(FVector::ZeroVector, FRotator::ZeroRotator);
        if (NewObject)
        {
            NewObject->SetActorHiddenInGame(true);
            NewObject->SetActorEnableCollision(false);
            PooledObjects.Add(NewObject);
        }
    }
}

AActor* UNDObjectPoolManager::GetPooledObject(const FVector& Position, const FRotator& Rotation)
{
    for (AActor* PooledObject : PooledObjects)
    {
        if (PooledObject && PooledObject->IsHidden())
        {
            PooledObject->SetActorLocation(Position);
            PooledObject->SetActorRotation(Rotation);
            PooledObject->SetActorHiddenInGame(false);
            PooledObject->SetActorEnableCollision(true);
            return PooledObject;
        }
    }

    // 부족하면 추가 생성
    AActor* NewObject = CreateNewObject(Position, Rotation);
    if (NewObject)
    {
        PooledObjects.Add(NewObject);
        return NewObject;
    }
    return nullptr;
}

void UNDObjectPoolManager::ReturnToPool(AActor* ActorToReturn)
{
    if (ActorToReturn)
    {
        ActorToReturn->SetActorHiddenInGame(true);
        ActorToReturn->SetActorEnableCollision(false);
    }
}

AActor* UNDObjectPoolManager::CreateNewObject(const FVector& Position, const FRotator& Rotation)
{
    if (!World || !PooledObjectClass) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    return World->SpawnActor<AActor>(PooledObjectClass, Position, Rotation, SpawnParams);
}
