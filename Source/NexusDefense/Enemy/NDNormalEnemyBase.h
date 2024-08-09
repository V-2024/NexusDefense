// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/NDEnemyBase.h"
#include "AIController.h"
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

public:
	UPROPERTY(EditDefaultsOnly, Category = "EnemyAI")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAI")
	float PursuitRadius;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float AttackCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float AttackDamage;

private:
	float LastAttackTime = 0;
};
