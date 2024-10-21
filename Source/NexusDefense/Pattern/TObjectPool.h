// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

template<class T>
class NEXUSDEFENSE_API TObjectPool
{
public:
	TObjectPool(UWorld* InWorld, int32 InitialSize, TSubclassOf<T> ClassType);
	~TObjectPool();

	T* GetObject();
	void ReturnObject(T* Object);

private:
	UWorld* World;
	TArray<T*> Pool;
	TSubclassOf<T> Class;

	T* CreateNewObject();
};

template<class T>
TObjectPool<T>::TObjectPool(UWorld* InWorld, int32 InitialSize, TSubclassOf<T> ClassType)
	: World(InWorld), Class(ClassType)
{
	for (int32 i = 0; i < InitialSize; ++i)
	{
		T* NewObject = CreateNewObject();
		ReturnObject(NewObject);
	}
}

template<class T>
TObjectPool<T>::~TObjectPool()
{
	for (T* Object : Pool)
	{
		if (Object)
		{
			Object->Destroy();
		}
	}
	Pool.Empty();
}

template<class T>
T* TObjectPool<T>::GetObject()
{
	if (Pool.Num() == 0)
	{
		return CreateNewObject();
	}

	T* Object = Pool.Pop();
	Object->SetActorHiddenInGame(false);
	Object->SetActorEnableCollision(true);
	return Object;
}

template<class T>
void TObjectPool<T>::ReturnObject(T* Object)
{
	if (Object)
	{
		Object->SetActorHiddenInGame(true);
		Object->SetActorEnableCollision(false);
		Pool.Push(Object);
	}
}

template<class T>
T* TObjectPool<T>::CreateNewObject()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return World->SpawnActor<T>(Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}