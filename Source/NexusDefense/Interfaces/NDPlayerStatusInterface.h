// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDPlayerStatusInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNDPlayerStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEXUSDEFENSE_API INDPlayerStatusInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void AddExperience(float Amount) = 0;

	UFUNCTION()
	virtual void AddHealth(float Amount) = 0;
};
