// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/NDBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANDBaseCharacter::ANDBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Camera Boom 설정
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength = 500.f;
    CameraBoom->bUsePawnControlRotation = true;

    // Camera 설정
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 기본 컴포넌트 생성
    HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));
    ExperienceComponent = CreateDefaultSubobject<UNDExperienceComponent>(TEXT("ExperienceComponent"));

    // 캐릭터 회전 설정
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    // 이동 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 100.f;
    GetCharacterMovement()->AirControl = 0.2f;
}

void ANDBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ANDBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ANDBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ANDBaseCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ANDBaseCharacter::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void ANDBaseCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ANDBaseCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ANDBaseCharacter::Turn(float Value)
{
    if (Controller && Value != 0.0f)
    {
        AddControllerYawInput(Value);
    }
}

void ANDBaseCharacter::LookUp(float Value)
{
    if (Controller && Value != 0.0f)
    {
        AddControllerPitchInput(Value);
    }
}

void ANDBaseCharacter::AddExperience(float Amount)
{
    if (ExperienceComponent)
    {
        ExperienceComponent->AddExperience(Amount);
    }
}

void ANDBaseCharacter::AddHealth(float Amount)
{
    if (HealthComponent)
    {
        HealthComponent->AddHealth(Amount);
    }
}

void ANDBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}
