// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/NDCombatComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UNDCombatComponent::UNDCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentState = ECombatState::None;
	CurrentSkillData = nullptr;
}

void UNDCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		OwnerCharacter = Cast<ACharacter>(Owner);
		AttacksComponent = Owner->FindComponentByClass<UNDAttacksComponent>();
	}
}

bool UNDCombatComponent::ExecuteSkill(FName SkillName)
{
	if (!OwnerCharacter.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid owner character"));
		return false;
	}

	UDataTable* DataTable = SkillDataTable.LoadSynchronous();
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load SkillDataTable"));
		return false;
	}

	FCombatSkillData* SkillData = DataTable->FindRow<FCombatSkillData>(SkillName, TEXT(""));
	if (!SkillData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill %s not found in data table"), *SkillName.ToString());
		return false;
	}

	FSkillState& State = SkillStates.FindOrAdd(SkillName);
	if (State.bIsOnCooldown)
	{
		UE_LOG(LogTemp, Verbose, TEXT("Skill %s is on cooldown"), *SkillName.ToString());
		return false;
	}

	if (UAnimMontage* Montage = SkillData->SkillMontage.LoadSynchronous())
	{
		CurrentSkillData = SkillData;
		OwnerCharacter->PlayAnimMontage(Montage);
		CurrentState = ECombatState::Attacking;
		CurrentSkillName = SkillName;

		StartCooldown(SkillName, SkillData->CoolTime);
		OnSkillExecuted.Broadcast(SkillName);

		return true;
	}

	return false;
}

bool UNDCombatComponent::IsSkillReady(FName SkillName) const
{
	const FSkillState* State = SkillStates.Find(SkillName);
	return !State || !State->bIsOnCooldown;
}

float UNDCombatComponent::GetSkillCooldownRemaining(FName SkillName) const
{
	const FSkillState* State = SkillStates.Find(SkillName);
	if (!State || !State->bIsOnCooldown)
	{
		return 0.0f;
	}

	UDataTable* DataTable = SkillDataTable.LoadSynchronous();
	if (!DataTable)
	{
		return 0.0f;
	}

	const FCombatSkillData* SkillData = DataTable->FindRow<FCombatSkillData>(SkillName, TEXT(""));
	if (!SkillData)
	{
		return 0.0f;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float TimeSinceUse = CurrentTime - State->LastUsedTime;
	return FMath::Max(0.0f, SkillData->CoolTime - TimeSinceUse);
}

void UNDCombatComponent::ProcessAttackHit()
{
	if (CurrentSkillData && AttacksComponent)
	{
		FND_S_AttackInfo AttackInfo;
		AttackInfo.DamageInfo.Amount = CurrentSkillData->Damage;

		AttacksComponent->ExecuteAttack(
			CurrentSkillData->AttackTraceType,
			AttackInfo,
			CurrentSkillData->HitRadius,
			CurrentSkillData->HitLength
		);
	}
}

void UNDCombatComponent::StartCooldown(FName SkillName, float CoolTime)
{
	FSkillState& State = SkillStates.FindOrAdd(SkillName);
	State.LastUsedTime = GetWorld()->GetTimeSeconds();
	State.bIsOnCooldown = true;

	if (State.CooldownTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(State.CooldownTimer);
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UNDCombatComponent::OnCooldownFinished, SkillName);
	GetWorld()->GetTimerManager().SetTimer(State.CooldownTimer, TimerDelegate, CoolTime, false);
}

void UNDCombatComponent::OnCooldownFinished(FName SkillName)
{
	if (FSkillState* State = SkillStates.Find(SkillName))
	{
		State->bIsOnCooldown = false;
		State->CooldownTimer.Invalidate();
		OnCooldownEnd.Broadcast(SkillName);
	}
}

void UNDCombatComponent::ResetSkillState()
{
	CurrentState = ECombatState::None;
	CurrentSkillName = NAME_None;
	CurrentSkillData = nullptr;
}