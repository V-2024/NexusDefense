// Fill out your copyright notice in the Description page of Project Settings.


#include "Pattern/NDHealthComponent.h"

void UNDHealthComponent::AddHealth(float Amount)
{
	CurrentHealth = FMath::Min(CurrentHealth + Amount, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	UE_LOG(LogTemp, Log, TEXT("Health gained: %f, CurrentHealth: %f"),
		Amount, CurrentHealth);
}
