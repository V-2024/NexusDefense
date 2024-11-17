// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NDHealthComponent.h"

void UNDHealthComponent::AddHealth(float Amount)
{
    float OldHealth = CurrentHealth;
    
    CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
    float Delta = CurrentHealth - OldHealth;

    if (!FMath::IsNearlyZero(Delta))
    {
        OnHealthChanged.Broadcast(CurrentHealth, Delta);
    }
}
