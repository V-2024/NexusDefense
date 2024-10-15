// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NDAnimInstance.h"
#include "GameFramework//Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNDAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			CharacterPlayer = Cast<ANDCharacterPlayer>(Pawn);
		}
	}
}

void UNDAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			CharacterPlayer = Cast<ANDCharacterPlayer>(Pawn);
		}
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (CharacterPlayer == nullptr)
		{
			CharacterPlayer = Cast<ANDCharacterPlayer>(Pawn);
		}
	}
}
