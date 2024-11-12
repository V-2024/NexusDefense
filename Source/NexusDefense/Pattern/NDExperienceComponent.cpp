// Fill out your copyright notice in the Description page of Project Settings.


#include "Pattern/NDExperienceComponent.h"

void UNDExperienceComponent::AddExperience(float Amount)
{
    if (Amount <= 0) return;
    CurrentExperience += Amount;
    OnExperienceChanged.Broadcast(CurrentExperience);
    UE_LOG(LogTemp, Log, TEXT("Experience gained: %f, Total: %f"),
        Amount, CurrentExperience);
}
