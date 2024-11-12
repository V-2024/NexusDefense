// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDHealthItem.h"

void ANDHealthItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp,
		OtherBodyIndex, bFromSweep, SweepResult);

    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        if (UNDHealthComponent* HealthComp = Character->FindComponentByClass<UNDHealthComponent>())
        {
            HealthComp->AddHealth(HealAmount);
        }
        Destroy();
    }
}

void ANDHealthItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnOverlapEnd(OverlappedComponent,
        OtherActor, OtherComp, OtherBodyIndex);

    UE_LOG(LogTemp, Warning, TEXT("HealthItem::OnOverlapBegin()"));
}
