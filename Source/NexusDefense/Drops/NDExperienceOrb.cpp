// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDExperienceOrb.h"
#include "Interfaces/NDPlayerStatusInterface.h"
#include "Kismet/GameplayStatics.h"

ANDExperienceOrb::ANDExperienceOrb()
{
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANDExperienceOrb::OnOverlapBegin);
}

void ANDExperienceOrb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (INDPlayerStatusInterface* ExpInterface = Cast<INDPlayerStatusInterface>(OtherActor))
    {
        ExpInterface->AddExperience(ExperienceAmount);
        PlayGainEffect();
        PlayGainSound();
        Destroy(); // 후에 수정 예정
    }
}

void ANDExperienceOrb::PlayGainEffect()
{
    if (GainEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            GainEffect,
            GetActorLocation()
        );
    }
}

void ANDExperienceOrb::PlayGainSound()
{
    if (GainSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            GainSound,
            GetActorLocation()
        );
    }
}
