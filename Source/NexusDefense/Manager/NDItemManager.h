// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDItemManager.generated.h"

class ANDItemBase;
class ANDCharacterBase;
class UNDObjectPoolManager;

UCLASS()
class NEXUSDEFENSE_API UNDItemManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UNDItemManager();

	void Initialize(UNDObjectPoolManager* ObjectManager);
	void RegisterItem(ANDItemBase* Item);
	void UnregisterItem(ANDItemBase* Item);
	void ProcessItemEffect(ANDItemBase* Item, ANDCharacterBase* Character);

private:
	UPROPERTY()
	TArray<ANDItemBase*> ActiveItems;

	UPROPERTY()
	UNDObjectPoolManager* ObjectPoolManager;


};
