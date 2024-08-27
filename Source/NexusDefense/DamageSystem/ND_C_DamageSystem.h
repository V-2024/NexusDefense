// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ND_S_DamageInfo.h"
#include "ND_C_DamageSystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageResponseSignature, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, FS_DamageInfo);

enum class EDamageResult
{
	BlockDamage,
	DoDamage,
	NoDamage
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UND_C_DamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UND_C_DamageSystem();

	FORCEINLINE float GetMaxHealth() const { return CurrentHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	bool TakeDamage(FS_DamageInfo);

	float Heal(float);

	void SetHealth(FS_DamageInfo);

	void OnDeath() const;

	void OnDamageResponse(float Amount) const;

	EDamageResult CalculateDamageResult(bool, bool) const;

public:	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "HP")
	float MaxHealth;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "HP")
	float CurrentHealth;

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

	// OnDeath 이벤트 디스패처
	FOnDeathSignature OnDeathEvent;

	// OnDamageResponse 이벤트 디스패처
	FOnDamageResponseSignature OnDamageResponseEvent;

	// OnDamage 이벤트 디스패처
	FOnDamageSignature OnDamageSignature;
};
