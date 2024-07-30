// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Damageable.h"

// Sets default values for this component's properties
UC_Damageable::UC_Damageable()
{
	PrimaryComponentTick.bCanEverTick = true;

}

bool UC_Damageable::TakeDamage(FS_DamageInfo Damage_Info)
{
	if (!IsDead)
	{
		EDamageResult DamageResult = CalculateDamageResult(Damage_Info.ShouldDamageInvincible, Damage_Info.CanBeBlocked);

		if (DamageResult == EDamageResult::DoDamage)
		{
			Health -= Damage_Info.Amount;

			if (Health <= 0.0f)
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

EDamageResult UC_Damageable::CalculateDamageResult(bool ShouldDamageInvincible, bool CanBeBlocked) const
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

float UC_Damageable::Heal(float Amount)
{
	if (!IsDead)
	{
		Health += Amount;

		if (Health > MaxHealth)
		{
			Health = MaxHealth;
		}

		return Health;
	}

	return 0.0f;
}

void UC_Damageable::OnDeath() const
{
	if (IsDead)
	{
		OnDeathEvent.Broadcast();
	}
}

void UC_Damageable::OnDamageResponse() const
{
	OnDamageResponseEvent.Broadcast();
}