// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayerMelee.h"
#include "NDCharacterPlayerAssassin.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerAssassin : public ANDCharacterPlayerMelee
{
	GENERATED_BODY()

public:
	ANDCharacterPlayerAssassin();

protected:
	virtual void Attack() override;
	
};
