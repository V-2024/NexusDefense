// Fill out your copyright notice in the Description page of Project Settings.


#include "ND_C_DamageSystem.h"

// Sets default values for this component's properties
UND_C_DamageSystem::UND_C_DamageSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

bool UND_C_DamageSystem::TakeDamage(FS_DamageInfo Damage_Info)
{
	if (!IsDead)
	{
		EDamageResult DamageResult = CalculateDamageResult(Damage_Info.ShouldDamageInvincible, Damage_Info.CanBeBlocked);

		if (DamageResult == EDamageResult::DoDamage)
		{
			// To avoid being 0 or negative
			CurrentHealth -= FMath::Clamp<float>(Damage_Info.Amount, 0, Damage_Info.Amount);

			if (CurrentHealth <= 0.0f)
			{
				IsDead = true;
				OnDeath();

				return true;
			}
			else
			{
				OnDamageResponse();

				return true;
			}
		}

		else if (DamageResult == EDamageResult::BlockDamage)
		{
			return false;
		}

		else if (DamageResult == EDamageResult::NoDamage)
		{
			return false;
		}
	}

	return false;
}

EDamageResult UND_C_DamageSystem::CalculateDamageResult(bool ShouldDamageInvincible, bool CanBeBlocked) const
{
	if (!IsDead && (!IsInvincible || ShouldDamageInvincible))
	{
		if (CanBeBlocked && IsBlocking)
		{
			return EDamageResult::BlockDamage;
		}
		else
		{
			return EDamageResult::DoDamage;
		}
	}
	else
	{
		return EDamageResult::NoDamage;
	}
}

float UND_C_DamageSystem::Heal(float Amount)
{
	if (!IsDead)
	{
		CurrentHealth += Amount;

		if (CurrentHealth > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}

		return CurrentHealth;
	}

	return 0.0f;
}

void UND_C_DamageSystem::SetHealth(FS_DamageInfo)
{

}

void UND_C_DamageSystem::OnDeath() const
{
	if (IsDead)
	{
		OnDeathEvent.Broadcast();
	}
}

void UND_C_DamageSystem::OnDamageResponse() const
{
	OnDamageResponseEvent.Broadcast();
}