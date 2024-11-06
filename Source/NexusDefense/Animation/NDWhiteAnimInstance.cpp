// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NDWhiteAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/NDCharacterWhite.h"
#include "Kismet/KismetMathLibrary.h"

void UNDWhiteAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			CharacterWhite = Cast<ANDCharacterWhite>(Pawn);
		}
	}
}

void UNDWhiteAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

		if (Pawn)
		{
			CharacterWhite = Cast<ANDCharacterWhite>(Pawn);
		}
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		if (MovementSpeed > 0.f)
		{
			FRotator ActorRotation = Pawn->GetActorRotation();
			FRotator MovementRotation = LateralSpeed.Rotation();
			Direction = UKismetMathLibrary::NormalizedDeltaRotator(
				MovementRotation,
				ActorRotation
			).Yaw;
		}
		else
		{
			Direction = 0.f;
		}

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (CharacterWhite == nullptr)
		{
			CharacterWhite = Cast<ANDCharacterWhite>(Pawn);
		}
	}
}
