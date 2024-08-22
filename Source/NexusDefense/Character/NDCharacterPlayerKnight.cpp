// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerKnight.h"

ANDCharacterPlayerKnight::ANDCharacterPlayerKnight()
{
	AttackRange = 200.0f;
	AttackDamage = 20.0f;
}

void ANDCharacterPlayerKnight::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("PlayerKinght %s is attacking"), *GetName());
}
