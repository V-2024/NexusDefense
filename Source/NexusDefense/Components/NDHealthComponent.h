// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "Interfaces/NDDamageableInterface.h"
#include "NDHealthComponent.generated.h"

// Damage Result Enum
UENUM(BlueprintType)
enum class EDamageResult : uint8
{
    BlockDamage  UMETA(DisplayName = "BlockDamage"),
    DoDamage     UMETA(DisplayName = "DoDamage"),
    NoDamage     UMETA(DisplayName = "NoDamage")
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, const FND_S_DamageInfo&);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDHealthComponent : public UActorComponent, public INDDamageableInterface
{
    GENERATED_BODY()

public:
    UNDHealthComponent();

    // INDDamageableInterface
    virtual bool TakeDamage(const FND_S_DamageInfo& DamageInfo) override;
    virtual float GetHealth() const override { return CurrentHealth; }
    virtual float GetMaxHealth() const override { return MaxHealth; }
    virtual bool IsDead() const override { return bIsDead; }

    // Health Management
    UFUNCTION(BlueprintCallable)
    void AddHealth(float Amount);

    // Events
    FOnHealthChanged OnHealthChanged;
    FOnDeathSignature OnDeathEvent;
    FOnDamageSignature OnDamageEvent;

protected:
    // Health Properties
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float MaxHealth = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float CurrentHealth = 100.f;

    // Combat State
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    bool bIsInvincible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    bool bIsInterrupted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    bool bIsBlocking;

private:
    EDamageResult CalculateDamageResult(bool ShouldDamageInvincible, bool CanBeBlocked) const;
    void HandleDeath();
};
