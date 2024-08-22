// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerAssassin.h"

ANDCharacterPlayerAssassin::ANDCharacterPlayerAssassin()
{
	AttackRange = 200.0f;
	AttackDamage = 20.0f;
}

void ANDCharacterPlayerAssassin::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("PlayerAssassin %s is attacking"), *GetName());
}
