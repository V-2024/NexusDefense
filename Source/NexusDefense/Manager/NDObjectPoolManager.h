// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Pattern/NDPoolableComponent.h"
#include "NDObjectPoolManager.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDObjectPoolManager : public UObject
{
    GENERATED_BODY()


public:
    template<typename T>
    void Initialize(UWorld* WorldContext, TSubclassOf<T> ClassType, int32 InitialSize);

    template<typename T>
    T* GetPooledObject(const FVector& Position, const FRotator& Rotation);

    // 디버그용
    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void LogPoolStatus();

private:
    UPROPERTY()
    TArray<AActor*> PooledObjects;

    UPROPERTY()
    TSubclassOf<AActor> PooledObjectClass;

    UPROPERTY()
    UWorld* World;

    template<typename T>
    T* ExpandPool(int32 Count);
};

template<typename T>
void UNDObjectPoolManager::Initialize(UWorld* WorldContext, TSubclassOf<T> ClassType, int32 InitialSize)
{
    static_assert(TIsDerivedFrom<T, AActor>::Value, "T must derive from AActor");

    World = WorldContext;
    PooledObjectClass = ClassType;

    if (InitialSize > 0)
    {
        ExpandPool<T>(InitialSize);
    }
}

template<typename T>
T* UNDObjectPoolManager::GetPooledObject(const FVector& Position, const FRotator& Rotation)
{
    UE_LOG(LogTemp, Warning, TEXT("Trying to get pooled object"));

    for (AActor* Actor : PooledObjects)
    {
        if (!IsValid(Actor))
        {
            UE_LOG(LogTemp, Warning, TEXT("Actor is not valid"));
            continue;
        }

        // Cast<T> 체크
        T* TypedObject = Cast<T>(Actor);
        if (!TypedObject)
        {
            UE_LOG(LogTemp, Warning, TEXT("Cast to TypedObject failed"));
            continue;
        }

        // 인터페이스 컴포넌트 ㅠㅠ 체크
        UNDPoolableComponent* PoolableComponent = TypedObject->FindComponentByClass<UNDPoolableComponent>();
        if (!PoolableComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("PoolableComponent not found"));
            continue;
        }

        // 활성화 상태 체크
        if (!PoolableComponent->IsPoolableActive())
        {
            UE_LOG(LogTemp, Warning, TEXT("Found inactive object in pool"));
            TypedObject->SetActorLocation(Position);
            TypedObject->SetActorRotation(Rotation);
            PoolableComponent->ActivatePoolable();
            return TypedObject;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Object is still active"));
        }
    }

    //for (AActor* Actor : PooledObjects)
    //{
    //    if (!IsValid(Actor))
    //    {
    //        continue;
    //    }

    //    if (T* TypedObject = Cast<T>(Actor))
    //    {
    //        INDPoolableInterface* Poolable = Cast<INDPoolableInterface>(Actor);
    //        if (Poolable && !Poolable->IsPoolableActive())
    //        {
    //            UE_LOG(LogTemp, Warning, TEXT("Found inactive object in pool"));
    //            TypedObject->SetActorLocation(Position);
    //            TypedObject->SetActorRotation(Rotation);
    //            Poolable->ActivatePoolable();
    //            return TypedObject;
    //        }
    //    }
    //}
    //UE_LOG(LogTemp, Warning, TEXT("No inactive objects found, creating new one"));

    T* NewObject = ExpandPool<T>(1);
    if (NewObject)
    {
        NewObject->SetActorLocation(Position);
        NewObject->SetActorRotation(Rotation);
        if (INDPoolableInterface* Poolable = Cast<INDPoolableInterface>(NewObject))
        {
            Poolable->ActivatePoolable();
        }
        return NewObject;
    }

    return nullptr;
}

template<typename T>
T* UNDObjectPoolManager::ExpandPool(int32 Count)
{
    if (!World || !PooledObjectClass)
        return nullptr;

    T* LastCreated = nullptr;

    for (int32 i = 0; i < Count; i++)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        if (T* NewObject = World->SpawnActor<T>(PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams))
        {
            PooledObjects.Add(NewObject);
            if (INDPoolableInterface* Poolable = Cast<INDPoolableInterface>(NewObject))
            {
                Poolable->DeactivatePoolable();
            }
            LastCreated = NewObject;
        }
    }

    return LastCreated;
}
