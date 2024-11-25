
#include "Components/NDAttacksComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/NDHealthComponent.h"

UNDAttacksComponent::UNDAttacksComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UNDAttacksComponent::BeginPlay()
{
    Super::BeginPlay();
    OwnerCharacter = Cast<ACharacter>(GetOwner());
}

bool UNDAttacksComponent::ExecuteAttack(EAttackTraceType TraceType, const FND_S_AttackInfo& AttackInfo, float Radius, float Length)
{
    if (!OwnerCharacter.IsValid())
    {
        return false;
    }

    switch (TraceType)
    {
    case EAttackTraceType::SphereTrace:
        return DoSphereTrace(AttackInfo, Radius, Length);
    case EAttackTraceType::LineTrace:
        return DoLineTrace(AttackInfo, Length);
    case EAttackTraceType::Overlapping:
        return DoOverlapping(AttackInfo, Radius);
    default:
        return false;
    }
}

bool UNDAttacksComponent::DoSphereTrace(const FND_S_AttackInfo& AttackInfo, float Radius, float Length)
{
    if (!OwnerCharacter.IsValid())
    {
        return false;
    }

    const FVector Start = OwnerCharacter->GetActorLocation();
    const FVector End = Start + (OwnerCharacter->GetActorForwardVector() * Length);

    TArray<FHitResult> HitResults;
    TArray<AActor*> ActorsToIgnore = { OwnerCharacter.Get() };

    bool bHit = UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        Start,
        End,
        Radius,
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        ActorsToIgnore,
        bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
        HitResults,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        DebugDrawTime
    );

    bool bAnyHit = false;
    TSet<AActor*> HitActors;

    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            if (AActor* HitActor = Hit.GetActor())
            {
                if (!HitActors.Contains(HitActor))
                {
                    ProcessHit(HitActor, AttackInfo);
                    HitActors.Add(HitActor);
                    bAnyHit = true;
                }
            }
        }
    }

    return bAnyHit;
}

bool UNDAttacksComponent::DoLineTrace(const FND_S_AttackInfo& AttackInfo, float Length)
{
    if (!OwnerCharacter.IsValid())
    {
        return false;
    }

    const FVector Start = OwnerCharacter->GetActorLocation();
    const FVector End = Start + (OwnerCharacter->GetActorForwardVector() * Length);

    FHitResult HitResult;
    bool bHit = UKismetSystemLibrary::LineTraceSingle(
        GetWorld(),
        Start,
        End,
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        TArray<AActor*>{OwnerCharacter.Get()},
        bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
        HitResult,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        DebugDrawTime
    );

    if (bHit && HitResult.GetActor())
    {
        ProcessHit(HitResult.GetActor(), AttackInfo);
        return true;
    }

    return false;
}

bool UNDAttacksComponent::DoOverlapping(const FND_S_AttackInfo& AttackInfo, float Radius)
{
    if (!OwnerCharacter.IsValid())
    {
        return false;
    }

    const FVector Location = OwnerCharacter->GetActorLocation();

    TArray<AActor*> OverlappedActors;
    const bool bOverlapped = UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        Location,
        Radius,
        TArray<TEnumAsByte<EObjectTypeQuery>>(),
        nullptr,
        TArray<AActor*>{OwnerCharacter.Get()},
        OverlappedActors
    );

    if (bDrawDebug)
    {
        DrawDebugSphere(
            GetWorld(),
            Location,
            Radius,
            16,
            FColor::Blue,
            false,
            DebugDrawTime,
            0,
            3.0f
        );
    }

    bool bAnyHit = false;
    if (bOverlapped)
    {
        for (AActor* HitActor : OverlappedActors)
        {
            ProcessHit(HitActor, AttackInfo);
            bAnyHit = true;
        }
    }

    return bAnyHit;
}

void UNDAttacksComponent::ProcessHit(AActor* HitActor, const FND_S_AttackInfo& AttackInfo)
{
    if (UNDHealthComponent* HealthComp = HitActor->FindComponentByClass<UNDHealthComponent>())
    {
        FND_S_DamageInfo DamageInfo;
        DamageInfo.Amount = AttackInfo.Damage;
        HealthComp->TakeDamage(DamageInfo);
        OnAttackHit.Broadcast(HitActor, AttackInfo);
    }
}