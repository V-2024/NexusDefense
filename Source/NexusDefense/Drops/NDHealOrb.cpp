// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDHealOrb.h"
#include "Interfaces/NDPlayerStatusInterface.h"
#include "Kismet/GameplayStatics.h"

ANDHealOrb::ANDHealOrb()
{
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANDHealOrb::OnOverlapBegin);
}

void ANDHealOrb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (INDPlayerStatusInterface* HealthInterface = Cast<INDPlayerStatusInterface>(OtherActor))
    {
        HealthInterface->AddHealth(HealAmount);
        PlayGainEffect();
        PlayGainSound();
        Destroy();
    }
}

void ANDHealOrb::PlayGainEffect()
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

void ANDHealOrb::PlayGainSound()
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
