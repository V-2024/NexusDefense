
#include "Components/NDHealthComponent.h"

UNDHealthComponent::UNDHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    CurrentHealth = MaxHealth;
    bIsInvincible = false;
    bIsDead = false;
    bIsInterrupted = false;
    bIsBlocking = false;
}

void UNDHealthComponent::AddHealth(float Amount)
{
    if (bIsDead) return;

    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
    float Delta = CurrentHealth - OldHealth;

    if (!FMath::IsNearlyZero(Delta))
    {
        OnHealthChanged.Broadcast(CurrentHealth, Delta);
    }
}

bool UNDHealthComponent::TakeDamage(const FND_S_DamageInfo& DamageInfo)
{
    if (bIsDead) return false;

    EDamageResult DamageResult = CalculateDamageResult(
        DamageInfo.ShouldDamageInvincible,
        DamageInfo.CanBeBlocked
    );

    if (DamageResult == EDamageResult::DoDamage)
    {
        float OldHealth = CurrentHealth;
        CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageInfo.Amount);
        float Delta = OldHealth - CurrentHealth;

        OnHealthChanged.Broadcast(CurrentHealth, -Delta);
        OnDamageEvent.Broadcast(DamageInfo);

        if (CurrentHealth <= 0.0f)
        {
            HandleDeath();
            return true;
        }
        return true;
    }

    return false;
}

EDamageResult UNDHealthComponent::CalculateDamageResult(bool ShouldDamageInvincible, bool CanBeBlocked) const
{
    if (!bIsDead && (!bIsInvincible || ShouldDamageInvincible))
    {
        if (CanBeBlocked && bIsBlocking)
        {
            return EDamageResult::BlockDamage;
        }
        return EDamageResult::DoDamage;
    }
    return EDamageResult::NoDamage;
}

void UNDHealthComponent::HandleDeath()
{
    if (!bIsDead)
    {
        bIsDead = true;
        OnDeathEvent.Broadcast();
    }
}