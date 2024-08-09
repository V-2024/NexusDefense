// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/NDNormalEnemyBase.h"
#include "NDMeleeEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDMeleeEnemyBase : public ANDNormalEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void PerformAttack() override;

};
