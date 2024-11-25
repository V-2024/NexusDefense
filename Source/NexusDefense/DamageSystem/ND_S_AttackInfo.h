// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "ND_S_AttackInfo.generated.h"

USTRUCT(BlueprintType)
struct FND_S_AttackInfo
{
    GENERATED_BODY()

public:
    FND_S_AttackInfo()
        : Damage(0.0f)
        , DamageType(nullptr)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TSubclassOf<UDamageType> DamageType;
};

