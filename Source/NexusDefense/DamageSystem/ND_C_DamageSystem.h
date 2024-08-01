// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ND_S_DamageInfo.h"
#include "ND_C_DamageSystem.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsInterrup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 AttackTokenCount;
};
