// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NDPoolableComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UNDPoolableComponent::UNDPoolableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

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

