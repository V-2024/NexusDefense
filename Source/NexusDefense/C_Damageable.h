// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_DamageInfo.h"
#include "C_Damageable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageResponseSignature);

enum class EDamageResult
{
	BlockDamage,
	DoDamage,
	NoDamage
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UC_Damageable : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_Damageable();
	bool TakeDamage(FS_DamageInfo);
	EDamageResult CalculateDamageResult(bool, bool) const;
	float Heal(float);

	// OnDeath 이벤트 디스패처
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathSignature OnDeathEvent;

	// OnDamageResponse 이벤트 디스패처
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDamageResponseSignature OnDamageResponseEvent;

	// Death 함수 선언
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void OnDeath() const;

	// DamageResponse 함수 선언
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void OnDamageResponse() const;

public:	
	float Health;
	float MaxHealth;
	bool IsInvincible;
	bool IsDead;
	bool IsInterrup;
	bool IsBlocking;
	int32 AttackTokenCount;
};
