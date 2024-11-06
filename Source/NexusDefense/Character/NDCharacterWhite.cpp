// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterWhite.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ANDCharacterWhite::ANDCharacterWhite()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bLMBDown = false;
	bAttacking = false;
}

// Called every frame
void ANDCharacterWhite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANDCharacterWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this,
		&ANDCharacterWhite::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,
		&ANDCharacterWhite::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this,
		&ANDCharacterWhite::Turn);
	PlayerInputComponent->BindAxis("LookUp", this,
		&ANDCharacterWhite::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
		&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this,
		&ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this,
		&ANDCharacterWhite::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this,
		&ANDCharacterWhite::LMBUp);
}

void ANDCharacterWhite::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f && !bAttacking)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANDCharacterWhite::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f && !bAttacking)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ANDCharacterWhite::Turn(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void ANDCharacterWhite::LookUp(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void ANDCharacterWhite::LMBDown()
{
	bLMBDown = true;
	Attack();
}

void ANDCharacterWhite::LMBUp()
{
	bLMBDown = false;
}

// Called when the game starts or when spawned
void ANDCharacterWhite::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDCharacterWhite::Attack()
{
	bAttacking = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		int32 Section = FMath::RandRange(0, 1);
		switch (Section)
		{
		case 0:
			AnimInstance->Montage_Play(CombatMontage, 1.2f);
			AnimInstance->Montage_JumpToSection(FName("Attack_1"),
				CombatMontage);
			break;
		case 1:
			AnimInstance->Montage_Play(CombatMontage, 1.2f);
			AnimInstance->Montage_JumpToSection(FName("Attack_2"),
				CombatMontage);
			break;

		default:
			;
		}
	}
}

void ANDCharacterWhite::AttackEnd()
{
	bAttacking = false;
}
