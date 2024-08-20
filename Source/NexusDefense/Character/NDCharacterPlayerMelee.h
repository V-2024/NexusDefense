// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayer.h"
#include "NDCharacterPlayerMelee.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerMelee : public ANDCharacterPlayer
{
	GENERATED_BODY()
	
public:
	ANDCharacterPlayerMelee();

protected:
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackDamage;
};
