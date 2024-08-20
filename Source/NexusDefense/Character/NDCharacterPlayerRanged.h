// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayer.h"
#include "NDCharacterPlayerRanged.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerRanged : public ANDCharacterPlayer
{
	GENERATED_BODY()
	
public:
    ANDCharacterPlayerRanged();

protected:
    virtual void Attack() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 AmmoCapacity;
};
