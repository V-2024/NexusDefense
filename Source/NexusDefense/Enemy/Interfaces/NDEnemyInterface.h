// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNDEnemyInterface : public UInterface
{
	GENERATED_BODY()
};


class NEXUSDEFENSE_API INDEnemyInterface
{
	GENERATED_BODY()

public:
	// Combat
	virtual float	GetThreatLevel()				const = 0;
	virtual bool	CanBeStunned()					const = 0;
	virtual void	ApplyStun(float Duration) = 0;
	virtual bool	IsStunned() const = 0;
    
	// State Management
	virtual void	OnSpawn() = 0;
	virtual void	OnDeath() = 0;
	virtual void	OnHit() = 0;
    
	// Stats
	virtual float	GetAttackDamage() const = 0;
	virtual float	GetAttackRange() const = 0;
	virtual float	GetDetectionRange() const = 0;
};
