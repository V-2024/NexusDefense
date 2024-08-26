// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "NDComboActionData.h"
#include "DamageSystem/ND_C_DamageSystem.h"
#include "Components/WidgetComponent.h"

// Sets default values
ANDCharacterBase::ANDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->bOrientRotationToMovement = true; //여기 변경함.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	Health = 100.0f;
	MovementSpeed = 600.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Warrior.SK_CharM_Warrior'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/NexusDefense/Animations/ABP_NDCharacter.ABP_NDCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);

	}

    SetComponents();
}


void ANDCharacterBase::SetComponents()
{
    // Damage Component
    DamageableComponent = CreateDefaultSubobject<UND_C_DamageSystem>(TEXT("DamageableComponent"));

    // HP Bar Widget
    HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    HPBarWidget->SetupAttachment(GetMesh());
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

    static ConstructorHelpers::FClassFinder<UUserWidget> HPBarWidgetClassRef(TEXT("/Game/NexusDefense/UI/Combat/WBP_HPBar.WBP_HPBar_C"));

    if (HPBarWidgetClassRef.Class)
    {
        HPBarWidget->SetWidgetClass(HPBarWidgetClassRef.Class);
        HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
        HPBarWidget->SetDrawSize(FVector2D(200.0f, 15.0f));
        HPBarWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ANDCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void ANDCharacterBase::Attack()
{
	ProcessComboCommand();
}

void ANDCharacterBase::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

//void ANDCharacterBase::ComboActionBegin()
//{
//	CurrentCombo = 1;
//
//	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
//
//	const float AttackSpeedRate = 1.0f;
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
//
//	FOnMontageEnded EndDelegate;
//	EndDelegate.BindUObject(this, &ANDCharacterBase::ComboActionEnd);
//	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);
//
//	ComboTimerHandle.Invalidate();
//	SetComboCheckTimer();
//}
//
//void ANDCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
//{
//	ensure(CurrentCombo != 0);
//	CurrentCombo = 0;
//	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
//}
//
//void ANDCharacterBase::SetComboCheckTimer()
//{
//	if (GetWorld() == nullptr)
//	{
//		UE_LOG(LogTemp, Error, TEXT("SetComboCheckTimer: World is null"));
//		return;
//	}
//	int32 ComboIndex = CurrentCombo - 1;
//	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));
//
//	const float AttackSpeedRate = 1.0f;
//	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
//	if (ComboEffectiveTime > 0.0f)
//	{
//		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ANDCharacterBase::ComboCheck, ComboEffectiveTime, false);
//	}
//}
//
//void ANDCharacterBase::ComboCheck()
//{
//	ComboTimerHandle.Invalidate();
//	if (HasNextComboCommand)
//	{
//		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//
//		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
//		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
//		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
//		SetComboCheckTimer();
//		HasNextComboCommand = false;
//	}
//}
void ANDCharacterBase::ComboActionBegin()
{
    if (!IsValid(GetCharacterMovement()))
    {
        UE_LOG(LogTemp, Error, TEXT("ComboActionBegin: CharacterMovement is invalid"));
        return;
    }

    CurrentCombo = 1;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

    UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
    if (!AnimInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("ComboActionBegin: AnimInstance is null"));
        return;
    }

    if (!ComboActionMontage)
    {
        UE_LOG(LogTemp, Error, TEXT("ComboActionBegin: ComboActionMontage is null"));
        return;
    }

    const float AttackSpeedRate = 1.0f;
    AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &ANDCharacterBase::ComboActionEnd);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

    ComboTimerHandle.Invalidate();
    SetComboCheckTimer();
}

void ANDCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
    if (CurrentCombo == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ComboActionEnd: CurrentCombo is already 0"));
    }
    else
    {
        ensure(CurrentCombo != 0);
    }

    CurrentCombo = 0;

    if (!IsValid(GetCharacterMovement()))
    {
        UE_LOG(LogTemp, Error, TEXT("ComboActionEnd: CharacterMovement is invalid"));
        return;
    }

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ANDCharacterBase::SetComboCheckTimer()
{
    if (!GetWorld())
    {
        UE_LOG(LogTemp, Error, TEXT("SetComboCheckTimer: World is null"));
        return;
    }

    if (!ComboActionData)
    {
        UE_LOG(LogTemp, Error, TEXT("SetComboCheckTimer: ComboActionData is null"));
        return;
    }

    int32 ComboIndex = CurrentCombo - 1;
    if (!ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("SetComboCheckTimer: Invalid ComboIndex: %d"), ComboIndex);
        return;
    }

    const float AttackSpeedRate = 1.0f;
    float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
    if (ComboEffectiveTime <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetComboCheckTimer: ComboEffectiveTime is <= 0"));
        return;
    }

    GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ANDCharacterBase::ComboCheck, ComboEffectiveTime, false);
}

void ANDCharacterBase::ComboCheck()
{
    ComboTimerHandle.Invalidate();
    if (HasNextComboCommand)
    {
        UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
        if (!AnimInstance)
        {
            UE_LOG(LogTemp, Error, TEXT("ComboCheck: AnimInstance is null"));
            return;
        }

        if (!ComboActionData)
        {
            UE_LOG(LogTemp, Error, TEXT("ComboCheck: ComboActionData is null"));
            return;
        }

        if (!ComboActionMontage)
        {
            UE_LOG(LogTemp, Error, TEXT("ComboCheck: ComboActionMontage is null"));
            return;
        }

        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
        FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);

        if (!AnimInstance->Montage_IsPlaying(ComboActionMontage))
        {
            UE_LOG(LogTemp, Warning, TEXT("ComboCheck: ComboActionMontage is not playing"));
            return;
        }

        AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
        SetComboCheckTimer();
        HasNextComboCommand = false;
    }
}
