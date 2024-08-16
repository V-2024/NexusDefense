// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NDAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNDAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector ActorForwardDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FRotator ActorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float CalculatedDirection;

private:
	float CalculateDirection(const FVector& InVelocity, const FRotator& BaseRotation);
};
