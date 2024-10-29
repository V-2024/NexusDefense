// Fill out your copyright notice in the Description page of Project Settings.


#include "Pattern/NDPoolableComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UNDPoolableComponent::UNDPoolableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsActive = false;
}

// Called when the game starts
void UNDPoolableComponent::BeginPlay()
{
	Super::BeginPlay();

	DeactivatePoolable();

}

void UNDPoolableComponent::ActivatePoolable()
{
	if (!IsValid(GetOwner()))
		return;
	bIsActive = true;
	GetOwner()->SetActorHiddenInGame(false);
	GetOwner()->SetActorEnableCollision(true);
	GetOwner()->SetActorTickEnabled(true);

	if (UProjectileMovementComponent* ProjectileMovement = GetOwner()->FindComponentByClass<UProjectileMovementComponent>())
	{
		ProjectileMovement->SetActive(true);
	}

	if (AutoDeactivateTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DeactivationTimerHandle,
			this,
			&UNDPoolableComponent::ReturnToPool,
			AutoDeactivateTime, false
		);

	}
	OnPoolableActivated.Broadcast();
}

void UNDPoolableComponent::DeactivatePoolable()
{
	if (!IsValid(GetOwner()))
		return;

	bIsActive = false;
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);
	GetOwner()->SetActorTickEnabled(false);

	GetOwner()->SetActorLocation(FVector(0, 0, -10000.0f));

	if (UProjectileMovementComponent* ProjectileMovement = GetOwner()->FindComponentByClass<UProjectileMovementComponent>())
	{
		ProjectileMovement->StopMovementImmediately();  // 즉시 이동 중지
		ProjectileMovement->SetActive(false);  // 컴포넌트 비활성화
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DeactivationTimerHandle);
	}

	OnPoolableDeactivated.Broadcast();
}

bool UNDPoolableComponent::IsPoolableActive() const
{
	return bIsActive;;
}

void UNDPoolableComponent::ReturnToPool()
{
	DeactivatePoolable();
}

