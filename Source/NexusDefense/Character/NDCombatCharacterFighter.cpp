// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacterFighter.h"
#include "Animation/AnimMontage.h"
#include "Data/NDComboActionData.h"

ANDCombatCharacterFighter::ANDCombatCharacterFighter()
{
}

void ANDCombatCharacterFighter::BeginPlay()
{
	Super::BeginPlay();
}

void ANDCombatCharacterFighter::PressLMB()
{
	Super::PressLMB();
	ProcessComboCommand();
}

void ANDCombatCharacterFighter::PressKeyboard1()
{
	HandleAttack(FName("SkillA"));
}

void ANDCombatCharacterFighter::PressKeyboard2()
{
	HandleAttack(FName("SkillB"));
}

void ANDCombatCharacterFighter::PressKeyboard3()
{
	HandleAttack(FName("SkillC"));
}

void ANDCombatCharacterFighter::PressKeyboard4()
{
	HandleAttack(FName("SkillD"));
}

void ANDCombatCharacterFighter::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		hasNextComboCommand = false;
	}
	else
	{
		hasNextComboCommand = true;
	}
}

void ANDCombatCharacterFighter::ComboActionBegin()
{
	// 콤보 시작
	CurrentCombo = 1;

	// AttackingState로 변경 -> 이동 불가
	CombatComponent->CurrentState = ECombatState::Attacking;

	// Animation Setting
	const float AttackSpeedRate = 1.0f;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ANDCombatCharacterFighter::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ANDCombatCharacterFighter::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	CombatComponent->CurrentState = ECombatState::None;
}

void ANDCombatCharacterFighter::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ANDCombatCharacterFighter::ComboCheck, ComboEffectiveTime, false);
	}
}

void ANDCombatCharacterFighter::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (hasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionPrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboCheckTimer();
		hasNextComboCommand = false;
	}
}

void ANDCombatCharacterFighter::ProcessAttackHit()
{
	if (!ComboActionData || !AttacksComponent)
	{
		return;
	}

	FND_S_AttackInfo AttackInfo;
	AttackInfo.DamageInfo.Amount = ComboActionData->ComboDamages.IsValidIndex(CurrentCombo - 1)
		? ComboActionData->ComboDamages[CurrentCombo - 1]
		: 10.0f;

	AttacksComponent->ExecuteAttack(
		EAttackTraceType::SphereTrace,
		AttackInfo,
		75.0f,
		200.0f
	);
}