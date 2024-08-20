// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerRifleman.h"

ANDCharacterPlayerRifleman::ANDCharacterPlayerRifleman()
{
	FireRate = 0.1f;
	AmmoCapacity = 30;
}

void ANDCharacterPlayerRifleman::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("Rifleman %s is attacking"), *GetName());
}
