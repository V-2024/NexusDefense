// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ND_S_DamageInfo.generated.h"

UENUM(BlueprintType)
enum class E_DamageType : uint8
{
    None UMETA(DisplayName = "None"),
    Melee UMETA(DisplayName = "Melee"),
    Projectile UMETA(DisplayName = "Projectile"),
    Explosion UMETA(DisplayName = "Explosion")
};

UENUM(BlueprintType)
enum class E_DamageResponse : uint8
{
    None UMETA(DisplayName = "None"),
    HitReaction UMETA(DisplayName = "Hit Reaction"),
    KnockBack UMETA(DisplayName = "Knock Back")
};

USTRUCT(BlueprintType)
struct FS_DamageInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Amount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    E_DamageType DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    E_DamageResponse DamageResponse;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ShouldDamageInvincible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool CanBeBlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ShouldForceInterrupt;

    FS_DamageInfo()
        : Amount(0.0f)
        , DamageType(E_DamageType::None)
        , DamageResponse(E_DamageResponse::None)
        , ShouldDamageInvincible(false)
        , CanBeBlocked(true)
        , ShouldForceInterrupt(false)
    {}
};