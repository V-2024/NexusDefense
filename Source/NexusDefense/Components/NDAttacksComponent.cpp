// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/NDAttacksComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

UNDAttacksComponent::UNDAttacksComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNDAttacksComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

bool UNDAttacksComponent::PrimaryMeleeAttack(const FND_S_AttackInfo& AttackInfo, float Radius, float Length)
{
    if (!OwnerCharacter)
    {
        return false;
    }

    FVector Start = OwnerCharacter->GetActorLocation();
    FVector End = Start + OwnerCharacter->GetActorForwardVector() * Length;

    TArray<FHitResult> HitResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerCharacter);

    bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, Sphere, QueryParams);

    bool bAnyDamageDealt = false;
    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            if (AActor* HitActor = Hit.GetActor())
            {
                UND_C_DamageSystem* DamageSystem = HitActor->FindComponentByClass<UND_C_DamageSystem>();
                if (DamageSystem)
                {
                    if (DamageSystem->TakeDamage(AttackInfo.DamageInfo))
                    {
                        bAnyDamageDealt = true;
                    }
                }
            }
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("PrimaryMeleeAttack end - Damage: %s"),
        bAnyDamageDealt ? TEXT("success") : TEXT("failed"));

    return bAnyDamageDealt;
}
