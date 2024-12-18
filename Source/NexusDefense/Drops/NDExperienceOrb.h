// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drops/NDItemBase.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "NDExperienceOrb.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDExperienceOrb : public ANDItemBase
{
	GENERATED_BODY()
	
public:
    ANDExperienceOrb();

protected:

    //경험치량
    UPROPERTY(EditAnywhere, Category = "Experience")
    float ExperienceAmount = 30.f;

    //이펙트
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
