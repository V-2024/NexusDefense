// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDExperienceOrb.h"

ANDExperienceOrb::ANDExperienceOrb()
{

}

void ANDExperienceOrb::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp,
		OtherBodyIndex, bFromSweep, SweepResult);

    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        // 경험치 증가 처리
        if (UNDExperienceComponent* ExpComp = Character->FindComponentByClass<UNDExperienceComponent>())
        {
            ExpComp->AddExperience(ExperienceAmount);
        }
        Destroy();
    }
}

void ANDExperienceOrb::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent,
		OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Warning, TEXT("ExperienceOrb::OnOverlapBegin()"));
}
