// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDCharacterPlayer.generated.h"

class AGun;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void Turn(float Value);
	void LookUp(float Value);

	void Shoot();
};
