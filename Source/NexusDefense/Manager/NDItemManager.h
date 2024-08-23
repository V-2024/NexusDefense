// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDItemManager.generated.h"

class ANDItemBase;
class ANDCharacterBase;

UCLASS()
class NEXUSDEFENSE_API ANDItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDItemManager();

	void RegisterItem(ANDItemBase* Item);
	void UnregisterItem(ANDItemBase* Item);
	void ProcessItemEffect(ANDItemBase* Item, ANDCharacterBase* Character);

private:
	UPROPERTY()
	TArray<ANDItemBase*> ActiveItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
