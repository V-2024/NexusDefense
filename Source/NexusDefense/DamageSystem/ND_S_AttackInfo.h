// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ND_S_DamageInfo.h"
#include "ND_S_AttackInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FND_S_AttackInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttackTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* Montage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FND_S_DamageInfo DamageInfo;

    FND_S_AttackInfo()
        : AttackTarget(NAME_None)
        , Montage(nullptr)
    {}
};

