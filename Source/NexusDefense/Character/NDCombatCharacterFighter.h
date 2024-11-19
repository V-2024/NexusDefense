// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCombatCharacter.h"
#include "NDCombatCharacterFighter.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCombatCharacterFighter : public ANDCombatCharacter
{
	GENERATED_BODY()
	
public:
	ANDCombatCharacterFighter();

protected:
	virtual void BeginPlay() override;

	virtual void PressKeyboard1() override;
	virtual void PressKeyboard2() override;
	virtual void PressKeyboard3() override;
	virtual void PressKeyboard4() override;

	// 고유한 기능 추후에 추가
};
