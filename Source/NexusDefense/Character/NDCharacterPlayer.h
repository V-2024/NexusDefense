// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDCharacterPlayer.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDCharacterPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* imc_ND;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_LookUp;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Turn;

	void Turn(const struct FInputActionValue& inputValue);
	void LookUp(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 600;

	FVector direction;

	void Move(const struct FInputActionValue& inputValue);

	void PlayerMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
