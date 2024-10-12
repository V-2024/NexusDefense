#include "NDObjectPoolManager.h"
#include "Math/UnrealMathUtility.h"


// 게임 종료 시 풀의 모든 오브젝트 제거 필요
// ReturnObjectPool 함수에서 오브젝트 초기화 필요
// 풀 정책 추가 필요 (LRU, MRU, FIFO, LIFO 등), 현재는 단순히 비활성화 오브젝트 찾아 반환

UNDObjectPoolManager::UNDObjectPoolManager()
{

}


void UNDObjectPoolManager::InitializePool(TSubclassOf<AActor> ActorClass, int32 PoolSize)
{
    if (!ObjectPools.Contains(ActorClass))
    {
        FObjectPoolData& NewPool = ObjectPools.Add(ActorClass);
        ExpandPool(ActorClass, PoolSize);
    }
}


void UNDObjectPoolManager::ExpandPool(TSubclassOf<AActor> ActorClass, int32 AdditionalSize)
{
    FObjectPoolData& Pool = ObjectPools[ActorClass];

    for (int32 i = 0; i < AdditionalSize; ++i)
    {
        AActor* NewObject = CreateNewObject(ActorClass);
        if (NewObject)
        {
            Pool.InactiveObjects.Add(NewObject);
            Pool.PoolSize++;
        }
    }
}



AActor* UNDObjectPoolManager::GetPooledObject(TSubclassOf<AActor> ActorClass)
{
    if (!ObjectPools.Contains(ActorClass))
    {
        InitializePool(ActorClass, DefaultPoolSize);
    }

    FObjectPoolData& Pool = ObjectPools[ActorClass];

    if (Pool.InactiveObjects.Num() == 0)
    {
        ExpandPool(ActorClass, FMath::Max(1, static_cast<int32>(Pool.PoolSize * (PoolExpansionFactor - 1))));
    }

    AActor* PooledObject = Pool.InactiveObjects.Pop();
    Pool.ActiveObjects.Add(PooledObject);

    if (PooledObject)
    {
        PooledObject->SetActorTickEnabled(true);
        PooledObject->SetActorHiddenInGame(false);
        PooledObject->SetActorEnableCollision(true);
    }

    return PooledObject;
}


void UNDObjectPoolManager::ReturnObjectToPool(AActor* ActorToReturn)
{
	if (!ActorToReturn) return;

	for (auto& Pair : ObjectPools)
	{
		FObjectPoolData& Pool = Pair.Value;
		int32 Index = Pool.ActiveObjects.Find(ActorToReturn);
		if (Index != INDEX_NONE)
		{
			Pool.ActiveObjects.RemoveAtSwap(Index);
			Pool.InactiveObjects.Add(ActorToReturn);

			ActorToReturn->SetActorTickEnabled(false);
			ActorToReturn->SetActorHiddenInGame(true);
			ActorToReturn->SetActorEnableCollision(false);
			ActorToReturn->SetActorLocation(FVector(0, 0, -10000));

			return;
		}
	}
}


void UNDObjectPoolManager::CleanupPool()
{
	for (auto& Pair : ObjectPools)
	{
		FObjectPoolData& Pool = Pair.Value;
		for (AActor* Object : Pool.ActiveObjects)
		{
			if (Object) Object->Destroy();
		}
		for (AActor* Object : Pool.InactiveObjects)
		{
			if (Object) Object->Destroy();
		}
		Pool.ActiveObjects.Empty();
		Pool.InactiveObjects.Empty();
		Pool.PoolSize = 0;
	}
	ObjectPools.Empty();
}



AActor* UNDObjectPoolManager::CreateNewObject(TSubclassOf<AActor> ActorClass)
{
	if (!ActorClass || !GetWorld()) return nullptr;

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


