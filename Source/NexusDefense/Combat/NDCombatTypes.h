#pragma once

#include "CoreMinimal.h"
#include "NDCombatTypes.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
    None        UMETA(DisplayName = "None"),
    Attacking   UMETA(DisplayName = "Attacking"),
    Stunned     UMETA(DisplayName = "Stunned"),
    Dead        UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EAttackTraceType : uint8
{
    SphereTrace  UMETA(DisplayName = "SphereTrace"),
    LineTrace    UMETA(DisplayName = "LineTrace"),
    Overlapping  UMETA(DisplayName = "Overlapping")
};