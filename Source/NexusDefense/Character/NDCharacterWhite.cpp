// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterWhite.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));
	ExperienceComponent = CreateDefaultSubobject<UNDExperienceComponent>(TEXT("ExperienceComponent"));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bAttacking = false;
	bLMBDown = false;
	CurrentAttackType = EAttackType::None;
}

// Called every frame
void ANDCharacterWhite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANDCharacterWhite::AddExperience(float Amount)
{
	if (ExperienceComponent)
	{
		ExperienceComponent->AddExperience(Amount);
	}
}

void ANDCharacterWhite::AddHealth(float Amount)
{
	if (HealthComponent)
	{
		HealthComponent->AddHealth(Amount);
	}
}

// Called to bind functionality to input
void ANDCharacterWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANDCharacterWhite::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANDCharacterWhite::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ANDCharacterWhite::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ANDCharacterWhite::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &ANDCharacterWhite::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &ANDCharacterWhite::LMBUp);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ANDCharacterWhite::InputAttack1);
	PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &ANDCharacterWhite::InputAttack2);
	PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &ANDCharacterWhite::InputAttack3);
	PlayerInputComponent->BindAction("Attack4", IE_Pressed, this, &ANDCharacterWhite::InputAttack4);
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
	UE_LOG(LogTemp, Display, TEXT("LMBDown"));
}

void ANDCharacterWhite::LMBUp()
{
	bLMBDown = false;
	UE_LOG(LogTemp, Display, TEXT("LMBUp"));
}

// Called when the game starts or when spawned
void ANDCharacterWhite::BeginPlay()
{
	Super::BeginPlay();
}

void ANDCharacterWhite::InputAttack1()
{
	if (!bAttacking)
	{
		ExecuteAttack(EAttackType::Attack1);
	}
}

void ANDCharacterWhite::InputAttack2()
{
	if (!bAttacking)
	{
		ExecuteAttack(EAttackType::Attack2);
	}
}

void ANDCharacterWhite::InputAttack3()
{
	if (!bAttacking)
	{
		ExecuteAttack(EAttackType::Attack3);
	}
}

void ANDCharacterWhite::InputAttack4()
{
	if (!bAttacking)
	{
		ExecuteAttack(EAttackType::Attack4);
	}
}

void ANDCharacterWhite::ExecuteAttack(EAttackType AttackType)
{
	
}