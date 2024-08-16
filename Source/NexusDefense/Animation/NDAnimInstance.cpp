// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NDAnimInstance.h"
#include "GameFramework//Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UNDAnimInstance::UNDAnimInstance()
{
	MovingThreshold = 3.0f;
	JumpingThreshold = 100.0f;
	ActorForwardDirection = FVector::ForwardVector;
	ActorRotation = FRotator::ZeroRotator;
	CalculatedDirection = 0.0f;
}

void UNDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UNDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshold;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);

		// 1. GetOwningActor()를 사용한 전방 벡터
		ActorForwardDirection = Owner->GetActorForwardVector();

		// 2. GetActorRotation()을 사용한 회전
		ActorRotation = Owner->GetActorRotation();

		// 3. 수동으로 방향 계산
		CalculatedDirection = CalculateDirection(Velocity, ActorRotation);
	}
}

float UNDAnimInstance::CalculateDirection(const FVector& InVelocity, const FRotator& BaseRotation)
{
	if (InVelocity.SizeSquared() > KINDA_SMALL_NUMBER)
	{
		FMatrix RotMatrix = FRotationMatrix(BaseRotation);
		FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		FVector NormalizedVel = InVelocity.GetSafeNormal2D();

		// Get the angle between the velocity and the forward vector
		float ForwardCosAngle = FVector::DotProduct(ForwardVector, NormalizedVel);
		float ForwardDeltaAngle = FMath::Acos(ForwardCosAngle);

		// Get the angle between the velocity and the right vector
		float RightCosAngle = FVector::DotProduct(RightVector, NormalizedVel);
		if (RightCosAngle < 0)
		{
			ForwardDeltaAngle *= -1.f;
		}

		return FMath::RadiansToDegrees(ForwardDeltaAngle);
	}
	return 0.f;
}
