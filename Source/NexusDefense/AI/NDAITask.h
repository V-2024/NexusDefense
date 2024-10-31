#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "NDAITask.generated.h"

USTRUCT(BlueprintType)
struct NEXUSDEFENSE_API FNDAITask
{
    GENERATED_BODY()

public:
    FNDAITask();

    UPROPERTY()
    class ANDEnemy* Enemy;

    UPROPERTY()
    ACharacter* Player;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInAttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShouldMove;
};