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

bool UNDAttacksComponent::ExecuteAttack(EAttackTraceType TraceType, const FND_S_AttackInfo& AttackInfo, float Radius, float Length)
{
	if (!OwnerCharacter) return false;

	// 傍拜 鸥涝
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

bool UNDAttacksComponent::DoLineTrace(const FND_S_AttackInfo& AttackInfo, float Length)
{
	if (!OwnerCharacter) return false;

	const FVector Start = OwnerCharacter->GetActorLocation();
	const FVector End = Start + (OwnerCharacter->GetActorForwardVector() * Length);

	FHitResult HitResult;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Pawn), false,
		TArray<AActor*>{OwnerCharacter}, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 3.0f);

	// 单固瘤 贸府
	if (bHit && HitResult.GetActor())
	{
		if (UND_C_DamageSystem* DamageSystem = HitResult.GetActor()->FindComponentByClass<UND_C_DamageSystem>())
		{
			return DamageSystem->TakeDamage(AttackInfo.DamageInfo);
		}
	}

	return false;
}

bool UNDAttacksComponent::DoSphereTrace(const FND_S_AttackInfo& AttackInfo, float Radius, float Length)
{
	if (!OwnerCharacter) return false;

	const FVector Start = OwnerCharacter->GetActorLocation();
	const FVector End = Start + (OwnerCharacter->GetActorForwardVector() * Length);

	TArray<FHitResult> HitResults;
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, Radius, UEngineTypes::ConvertToTraceType(ECC_Pawn), false,
		TArray<AActor*>{OwnerCharacter}, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, 3.0f
	);

	// 单固瘤 贸府
	bool bAnyDamageDealt = false;
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			if (AActor* HitActor = Hit.GetActor())
			{
				if (UND_C_DamageSystem* DamageSystem = HitActor->FindComponentByClass<UND_C_DamageSystem>())
				{
					if (DamageSystem->TakeDamage(AttackInfo.DamageInfo))
					{
						bAnyDamageDealt = true;
					}
				}
			}
		}
	}

	return bAnyDamageDealt;
}

bool UNDAttacksComponent::DoOverlapping(const FND_S_AttackInfo& AttackInfo, float Radius)
{
	if (!OwnerCharacter) return false;

	const FVector Location = OwnerCharacter->GetActorLocation();

	TArray<AActor*> OverlappedActors;
	const bool bOverlapped = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Location, Radius, TArray<TEnumAsByte<EObjectTypeQuery>>(),
		nullptr, TArray<AActor*>{OwnerCharacter}, OverlappedActors);

	DrawDebugSphere(GetWorld(), Location, Radius, 16, FColor::Blue, false, 3.0f, 0, 3.0f);

	// 单固瘤 贸府
	bool bAnyDamageDealt = false;
	if (bOverlapped)
	{
		for (AActor* HitActor : OverlappedActors)
		{
			if (UND_C_DamageSystem* DamageSystem = HitActor->FindComponentByClass<UND_C_DamageSystem>())
			{
				if (DamageSystem->TakeDamage(AttackInfo.DamageInfo))
				{
					bAnyDamageDealt = true;
				}
			}
		}
	}

	return bAnyDamageDealt;
}