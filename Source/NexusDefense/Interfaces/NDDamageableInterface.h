// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "NDDamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNDDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEXUSDEFENSE_API INDDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    
    virtual bool TakeDamage(const FND_S_DamageInfo& DamageInfo) = 0;
    virtual float GetHealth() const = 0;
    virtual float GetMaxHealth() const = 0;
    virtual bool IsDead() const = 0;
};
