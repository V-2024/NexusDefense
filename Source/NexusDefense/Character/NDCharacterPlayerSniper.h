// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayerRanged.h"
#include "NDCharacterPlayerSniper.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerSniper : public ANDCharacterPlayerRanged
{
	GENERATED_BODY()

public:
	ANDCharacterPlayerSniper();

protected:
	virtual void Attack() override;
	
};
