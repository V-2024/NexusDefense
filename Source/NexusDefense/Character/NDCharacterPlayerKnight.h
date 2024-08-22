// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayerMelee.h"
#include "NDCharacterPlayerKnight.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerKnight : public ANDCharacterPlayerMelee
{
	GENERATED_BODY()
	
public:
	ANDCharacterPlayerKnight();

protected:
	virtual void Attack() override;
};
