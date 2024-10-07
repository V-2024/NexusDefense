// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDItemManager.h"
#include "Item/NDItemBase.h"
#include "Manager/NDObjectPoolManager.h"

// Sets default values
UNDItemManager::UNDItemManager()
{


}

void UNDItemManager::Initialize(UNDObjectPoolManager* ObjectManager)
{
	if (ObjectManager)
	{
		ObjectPoolManager = ObjectManager;
	}
}

void UNDItemManager::RegisterItem(ANDItemBase* Item)
{
	if (Item)
	{
		ActiveItems.AddUnique(Item);
	}
}

void UNDItemManager::UnregisterItem(ANDItemBase* Item)
{
	if (Item)
	{
		ActiveItems.Remove(Item);
	}
}

void UNDItemManager::ProcessItemEffect(ANDItemBase* Item, ANDCharacterBase* Character)
{
	if (Item && Character)
	{
		Item->ApplyEffectToCharacter(Character);
		UnregisterItem(Item);
		Item->Destroy();
		UE_LOG(LogTemp, Log, TEXT("Hit with %s"), *GetName());
	}
}

