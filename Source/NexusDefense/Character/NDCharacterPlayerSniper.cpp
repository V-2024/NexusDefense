// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerSniper.h"

ANDCharacterPlayerSniper::ANDCharacterPlayerSniper()
{
	FireRate = 1.5f;
	AmmoCapacity = 30;
}

void ANDCharacterPlayerSniper::Attack()
{
	Super::Attack();

	UE_LOG(LogTemp, Warning, TEXT("Sniper %s is attacking"), *GetName());
}
