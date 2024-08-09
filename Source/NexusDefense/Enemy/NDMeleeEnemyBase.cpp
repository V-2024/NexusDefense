// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDMeleeEnemyBase.h"

void ANDMeleeEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDMeleeEnemyBase::PerformAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("PerformAttack"));
}