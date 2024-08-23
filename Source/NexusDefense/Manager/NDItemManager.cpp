// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDItemManager.h"

// Sets default values
ANDItemManager::ANDItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANDItemManager::RegisterItem(ANDItemBase* Item)
{
	if (Item)
	{
		ActiveItems.AddUnique(Item);
	}
}

void ANDItemManager::UnregisterItem(ANDItemBase* Item)
{
	if (Item)
	{
		ActiveItems.Remove(Item);
	}
}

void ANDItemManager::ProcessItemEffect(ANDItemBase* Item, ANDCharacterBase* Character)
{
	if (Item && Character)
	{
		Item->ApplyEffectToCharacter(Character);
		UnregisterItem(Item);
		Item->Destroy();
		UE_LOG(LogTemp, Log, TEXT("Hit with %s"), *GetName());
	}
}

// Called when the game starts or when spawned
void ANDItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

