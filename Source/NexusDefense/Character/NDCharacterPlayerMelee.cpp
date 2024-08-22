// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayerMelee.h"

ANDCharacterPlayerMelee::ANDCharacterPlayerMelee()
{
	AttackRange = 200.0f;
	AttackDamage = 20.0f;
}

void ANDCharacterPlayerMelee::Attack()
{
	
	UE_LOG(LogTemp, Warning, TEXT("ANDCharacterPlayerMelee::Attack() - Start"));
    Super::Attack();
    UE_LOG(LogTemp, Warning, TEXT("ANDCharacterPlayerMelee::Attack() - After Super::Attack()"));
	LevelUp();
    UE_LOG(LogTemp, Warning, TEXT("Melee character %s is attacking with range %f and damage %f"), *GetName(), AttackRange, AttackDamage);
}
