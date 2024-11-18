// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterWhite.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANDCharacterWhite::ANDCharacterWhite()
{
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 붐 설정
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	// 카메라 설정
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 컴포넌트 생성
	HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));
	ExperienceComponent = CreateDefaultSubobject<UNDExperienceComponent>(TEXT("ExperienceComponent"));
	CombatComponent = CreateDefaultSubobject<UNDCombatComponent>(TEXT("CombatComponent"));
	AttacksComponent = CreateDefaultSubobject<UNDAttacksComponent>(TEXT("AttacksComponent"));

	// 캐릭터 회전 설정
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ANDCharacterWhite::BeginPlay()
{
	Super::BeginPlay();
}

void ANDCharacterWhite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDCharacterWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 이동 입력 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &ANDCharacterWhite::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANDCharacterWhite::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ANDCharacterWhite::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ANDCharacterWhite::LookUp);

	// 점프 입력 바인딩
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// 공격 입력 바인딩
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ANDCharacterWhite::PressKeyboard1);
	PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &ANDCharacterWhite::PressKeyboard2);
	PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &ANDCharacterWhite::PressKeyboard3);
	PlayerInputComponent->BindAction("Attack4", IE_Pressed, this, &ANDCharacterWhite::PressKeyboard4);
}

void ANDCharacterWhite::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANDCharacterWhite::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ANDCharacterWhite::Turn(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void ANDCharacterWhite::LookUp(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void ANDCharacterWhite::PressKeyboard1()
{
	if (CombatComponent)
	{
		CombatComponent->ExecuteSkill(FName("SkillA"));
	}
}

void ANDCharacterWhite::PressKeyboard2()
{
	if (CombatComponent)
	{
		CombatComponent->ExecuteSkill(FName("SkillB"));
	}
}

void ANDCharacterWhite::PressKeyboard3()
{
	if (CombatComponent)
	{
		CombatComponent->ExecuteSkill(FName("SkillC"));
	}
}

void ANDCharacterWhite::PressKeyboard4()
{
	if (CombatComponent)
	{
		CombatComponent->ExecuteSkill(FName("SkillD"));
	}
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