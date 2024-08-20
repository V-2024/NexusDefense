// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerRanged.h"

ANDCharacterPlayerRanged::ANDCharacterPlayerRanged()
{
	FireRate = 0.5f;
	AmmoCapacity = 30;
}

void ANDCharacterPlayerRanged::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("Ranged character %s is attacking with fire rate %f and ammo capacity %d"), *GetName(), FireRate, AmmoCapacity);
}
