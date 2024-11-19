// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/NDHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "NDDummyEnemy.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDDummyEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    ANDDummyEnemy();

protected:
    virtual void BeginPlay() override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNDHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* HealthBarWidget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HealthBarWidgetClass;

    // Event Handlers
    UFUNCTION()
    void OnDamageReceived(const FND_S_DamageInfo& DamageInfo);

    UFUNCTION()
    void OnDeath();

    // VFX/SFX
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* HitEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* DeathEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
    USoundBase* HitSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
    USoundBase* DeathSound;

private:
    void PlayHitEffects();
    void PlayDeathEffects();
};