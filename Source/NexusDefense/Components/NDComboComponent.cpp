#include "Components/NDComboComponent.h"
#include "GameFramework/Character.h"
#include "Combat/NDCombatComponent.h"
#include "Components/NDAttacksComponent.h"
#include "Animation/AnimInstance.h"
#include "Data/NDComboActionData.h"
#include "DamageSystem/ND_S_AttackInfo.h"

UNDComboComponent::UNDComboComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentCombo = 0;
    hasNextComboCommand = false;
}

void UNDComboComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter.IsValid())
    {
        CombatComponent = OwnerCharacter->FindComponentByClass<UNDCombatComponent>();
        AttacksComponent = OwnerCharacter->FindComponentByClass<UNDAttacksComponent>();
    }
}

void UNDComboComponent::ProcessComboCommand()
{
    if (!OwnerCharacter.IsValid() || !CombatComponent || !ComboActionData)
    {
        return;
    }

    if (CurrentCombo == 0)
    {
        ComboActionBegin();
        return;
    }

    if (ComboTimerHandle.IsValid())
    {
        hasNextComboCommand = true;
    }
}

void UNDComboComponent::ComboActionBegin()
{
    if (!ComboActionData || !ComboActionMontage || CombatComponent->GetCurrentState() != ECombatState::None)
    {
        return;
    }

    CurrentCombo = 1;
    CombatComponent->SetCurrentState(ECombatState::Attacking);

    if (UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance())
    {
        const float AttackSpeedRate = 1.0f;
        AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &UNDComboComponent::ComboActionEnd);
        AnimInstance->Montage_SetEndDelegate(EndDelegate);

        SetComboCheckTimer();
        OnComboUpdated.Broadcast(CurrentCombo);
    }
}

void UNDComboComponent::SetComboCheckTimer()
{
    if (ComboActionData && ComboActionData->EffectiveFrameCount.IsValidIndex(CurrentCombo - 1))
    {
        const float AttackSpeedRate = 1.0f;
        float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[CurrentCombo - 1] / ComboActionData->FrameRate) / AttackSpeedRate;

        if (ComboEffectiveTime > 0.0f)
        {
            GetWorld()->GetTimerManager().SetTimer(
                ComboTimerHandle,
                this,
                &UNDComboComponent::ComboCheck,
                ComboEffectiveTime,
                false
            );
        }
    }
}

void UNDComboComponent::ComboCheck()
{
    ComboTimerHandle.Invalidate();

    if (hasNextComboCommand && ComboActionData)
    {
        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

        if (UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance())
        {
            FName NextSection = *FString::Printf(TEXT("Combo%d"), CurrentCombo);
            AnimInstance->Montage_JumpToSection(NextSection);

            SetComboCheckTimer();
            OnComboUpdated.Broadcast(CurrentCombo);
        }

        hasNextComboCommand = false;
    }
}

void UNDComboComponent::ComboActionEnd(UAnimMontage* Montage, bool bInterrupted)
{
    CurrentCombo = 0;
    hasNextComboCommand = false;
    ComboTimerHandle.Invalidate();
    CombatComponent->SetCurrentState(ECombatState::None);
}

void UNDComboComponent::ProcessAttackHit()
{
    if (!ComboActionData || !AttacksComponent)
    {
        return;
    }

    FND_S_AttackInfo AttackInfo;
    AttackInfo.Damage = ComboActionData->ComboDamages.IsValidIndex(CurrentCombo - 1)
        ? ComboActionData->ComboDamages[CurrentCombo - 1]
        : 10.0f;

    AttacksComponent->ExecuteAttack(
        EAttackTraceType::SphereTrace,
        AttackInfo,
        75.0f,
        200.0f
    );
}