// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NDExperienceComponent.h"

void UNDExperienceComponent::AddExperience(float Amount)
{
    float OldExperience = CurrentExperience;
    CurrentExperience += Amount;

    OnExperienceChanged.Broadcast(CurrentExperience, Amount);
    CheckLevelUp();
}

void UNDExperienceComponent::CheckLevelUp()
{
    float RequiredExp = GetRequiredExperience();

    while (CurrentExperience >= RequiredExp)
    {
        CurrentExperience -= RequiredExp;
        CurrentLevel++;
        OnLevelUp.Broadcast(CurrentLevel);
        RequiredExp = GetRequiredExperience();
    }
}

float UNDExperienceComponent::GetRequiredExperience() const
{
    return BaseExperienceRequired * CurrentLevel;
}
