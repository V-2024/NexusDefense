// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/NDEnemyBase.h"
#include "AI/NDAICBase.h"
#include "NDNormalEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDNormalEnemyBase : public ANDEnemyBase
{
	GENERATED_BODY()
	
public:
	ANDNormalEnemyBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void PursuitPlayer();

	void AttackPlayer();

	virtual void PerformAttack();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float AttackCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float AttackDamage;

private:
	ANDAICBase* AIController;
	float LastAttackTime;
};
