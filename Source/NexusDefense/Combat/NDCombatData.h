// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NDCombatData.generated.h"

USTRUCT(BlueprintType)
struct FCombatSkillData : public FTableRowBase
{
    GENERATED_BODY()

public:
    FCombatSkillData()
        : AttackTraceType(EAttackTraceType::SphereTrace)
        , Damage(0.0f)
        , CoolTime(0.0f)
        , HitRadius(0.0f)
        , HitLength(0.0f)
        , bCanBeCombo(false)
    {
    }

    UPROPERTY(EditDefaultsOnly, Category = "Skill")
    FName SkillName;

    UPROPERTY(EditDefaultsOnly, Category = "Skill", meta = (AllowedClasses = "AnimMontage"))
    TSoftObjectPtr<UAnimMontage> SkillMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Skill")
    EAttackTraceType AttackTraceType;

    UPROPERTY(EditDefaultsOnly, Category = "Skill", meta = (ClampMin = "0.0"))
    float Damage;

    UPROPERTY(EditDefaultsOnly, Category = "Skill", meta = (ClampMin = "0.0"))
    float CoolTime;

    UPROPERTY(EditDefaultsOnly, Category = "Skill", meta = (ClampMin = "0.0"))
    float HitRadius;

    UPROPERTY(EditDefaultsOnly, Category = "Skill", meta = (ClampMin = "0.0"))
    float HitLength;

    UPROPERTY(EditDefaultsOnly, Category = "Skill")
    bool bCanBeCombo;
};

USTRUCT()
struct FSkillState
{
    GENERATED_BODY()

    FSkillState()
        : LastUsedTime(0.0f)
        , bIsOnCooldown(false)
    {
    }

    float LastUsedTime;
    bool bIsOnCooldown;
    FTimerHandle CooldownTimer;
};