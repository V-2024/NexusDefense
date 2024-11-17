// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drops/NDItemBase.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "NDHealOrb.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDHealOrb : public ANDItemBase
{
	GENERATED_BODY()

public:
    ANDHealOrb();

protected:
    UPROPERTY(EditAnywhere, Category = "Healing")
    float HealAmount = 25.f;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* GainEffect;

    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* GainSound;

    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult) override;

    void PlayGainEffect();
    void PlayGainSound();
	
};
