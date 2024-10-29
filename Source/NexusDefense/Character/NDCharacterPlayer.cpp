// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterPlayer.h"
#include "Weapon/Gun.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANDCharacterPlayer::ANDCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetRelativeLocation(FVector(0, 0, 90));
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ANDCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_l"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	Gun->SetOwner(this);
}

void ANDCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ANDCharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ANDCharacterPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ANDCharacterPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ANDCharacterPlayer::LookUpAtRate);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ANDCharacterPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ANDCharacterPlayer::LookUp);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ANDCharacterPlayer::StartFiring);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &ANDCharacterPlayer::StopFiring);
	PlayerInputComponent->BindAction(TEXT("ToggleCamera"), EInputEvent::IE_Pressed, this, &ANDCharacterPlayer::StartToggleCameraDistance);
	PlayerInputComponent->BindAction(TEXT("ToggleCamera"), EInputEvent::IE_Released, this, &ANDCharacterPlayer::StopToggleCameraDistance);
}

void ANDCharacterPlayer::MoveForward(float Value)
{
	//if (Controller != nullptr && Value != 0.0f)
	//{
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//	AddMovementInput(Direction, Value);
	//}
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		if (bIsFPSMode)
		{
			const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
		else
		{
			const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void ANDCharacterPlayer::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ANDCharacterPlayer::TurnAtRate(float Rate)
{
	if (Controller != nullptr && Rate != 0.0f)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ANDCharacterPlayer::LookUpAtRate(float Rate)
{
	if (Controller != nullptr && Rate != 0.0f)
	{
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ANDCharacterPlayer::Turn(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void ANDCharacterPlayer::LookUp(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void ANDCharacterPlayer::StartFiring()
{
	if (Gun)
	{
		Gun->PullTrigger();
	}
}

void ANDCharacterPlayer::StopFiring()
{
	if (Gun)
	{
		Gun->ReleaseTrigger();
	}
}

void ANDCharacterPlayer::StartToggleCameraDistance()
{
	if (CameraBoom)
	{
		float CurrentDistance = CameraBoom->TargetArmLength;
		TransitionAlpha = 0.0f;

		// FPS 모드로 전환
		SetFPSMode(true);

		GetWorld()->GetTimerManager().SetTimer(
			CameraTransitionTimerHandle,
			[this, CurrentDistance]()
			{
				TransitionAlpha += 0.06;
				if (TransitionAlpha >= 1.0f)
				{
					CameraBoom->TargetArmLength = CloseDistance;
					GetWorld()->GetTimerManager().ClearTimer(CameraTransitionTimerHandle);
					return;
				}

				CameraBoom->TargetArmLength = FMath::Lerp(CurrentDistance, CloseDistance, TransitionAlpha);
			},
			0.008,
			true
		);
	}
}

void ANDCharacterPlayer::StopToggleCameraDistance()
{
	if (CameraBoom)
	{
		float CurrentDistance = CameraBoom->TargetArmLength;
		TransitionAlpha = 0.0f;

		// TPS 모드로 복귀
		SetFPSMode(false);

		GetWorld()->GetTimerManager().SetTimer(
			CameraTransitionTimerHandle,
			[this, CurrentDistance]()
			{
				TransitionAlpha += 0.06;
				if (TransitionAlpha >= 1.0f)
				{
					CameraBoom->TargetArmLength = FarDistance;
					GetWorld()->GetTimerManager().ClearTimer(CameraTransitionTimerHandle);
					return;
				}

				CameraBoom->TargetArmLength = FMath::Lerp(CurrentDistance, FarDistance, TransitionAlpha);
			},
			0.008,
			true
		);
	}
}

void ANDCharacterPlayer::SetFPSMode(bool bEnabled)
{
	bIsFPSMode = bEnabled;

	if (bEnabled)
	{
		// 모드 설정
		bOriginalUseControllerRotationYaw = bUseControllerRotationYaw;
		bOriginalOrientRotationToMovement = GetCharacterMovement()->bOrientRotationToMovement;

		bUseControllerRotationYaw = true;  
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		bUseControllerRotationYaw = bOriginalUseControllerRotationYaw;
		GetCharacterMovement()->bOrientRotationToMovement = bOriginalOrientRotationToMovement;

		if (CameraBoom)
		{
			CameraBoom->SocketOffset = FVector::ZeroVector;
			CameraBoom->TargetOffset = FVector::ZeroVector;
		}
	}
}
