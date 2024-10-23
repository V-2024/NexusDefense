#include "NDObjectPoolManager.h"

#include "Manager/NDObjectPoolManager.h"

void UNDObjectPoolManager::LogPoolStatus()
{
    int32 ActiveCount = 0;
    for (AActor* Object : PooledObjects)
    {
        if (!IsValid(Object)) continue;

        INDPoolableInterface* Poolable = Cast<INDPoolableInterface>(Object);
        if (Poolable && Poolable->IsPoolableActive())
        {
            ActiveCount++;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Pool Status - Active: %d, Total: %d"),
        ActiveCount, PooledObjects.Num());
}