// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterPlayerRanged.h"
#include "NDCharacterPlayerRifleman.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayerRifleman : public ANDCharacterPlayerRanged
{
	GENERATED_BODY()
	
public:
	ANDCharacterPlayerRifleman();

protected:
	virtual void Attack() override;
};
