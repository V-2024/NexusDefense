#include "Components/NDSkillComponent.h"
#include "GameFramework/Character.h"
#include "Combat/NDCombatComponent.h"
#include "NDAttacksComponent.h"
#include "Animation/AnimMontage.h"
#include "Engine/DataTable.h"

UNDSkillComponent::UNDSkillComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UNDSkillComponent::BeginPlay()
{
    Super::BeginPlay();

    // �ʿ��� ������Ʈ�� ã��
    OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter.IsValid())
    {
        CombatComponent = OwnerCharacter->FindComponentByClass<UNDCombatComponent>();
        AttacksComponent = OwnerCharacter->FindComponentByClass<UNDAttacksComponent>();
    }
}

bool UNDSkillComponent::ExecuteSkill(FName SkillName)
{
    if (!OwnerCharacter.IsValid() || !CombatComponent || !AttacksComponent)
    {
        return false;
    }

    // ���� ��ų ��� ���� �������� Ȯ��
    if (CombatComponent->GetCurrentState() != ECombatState::None)
    {
        return false;
    }

    // ��ų ������ �ε�
    UDataTable* DataTable = SkillDataTable.LoadSynchronous();
    if (!DataTable)
    {
        return false;
    }

    FCombatSkillData* SkillData = DataTable->FindRow<FCombatSkillData>(SkillName, TEXT(""));
    if (!SkillData)
    {
        return false;
    }

    // ��ٿ� üũ
    if (!IsSkillReady(SkillName))
    {
        return false;
    }

    // ��ų ����
    if (UAnimMontage* Montage = SkillData->SkillMontage.LoadSynchronous())
    {
        OwnerCharacter->PlayAnimMontage(Montage);
        CombatComponent->SetCurrentState(ECombatState::Attacking);

        // ��ٿ� ����
        StartCooldown(SkillName, SkillData->CoolTime);
        OnSkillExecuted.Broadcast(SkillName, SkillData->CoolTime);

        return true;
    }

    return false;
}

bool UNDSkillComponent::IsSkillReady(FName SkillName) const
{
    const FSkillState* State = SkillStates.Find(SkillName);
    return !State || !State->bIsOnCooldown;
}

float UNDSkillComponent::GetSkillCooldownRemaining(FName SkillName) const
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

void UNDSkillComponent::StartCooldown(FName SkillName, float CoolTime)
{
    FSkillState& State = SkillStates.FindOrAdd(SkillName);
    State.LastUsedTime = GetWorld()->GetTimeSeconds();
    State.bIsOnCooldown = true;

    // ��ٿ� Ÿ�̸� ����
    FTimerHandle& TimerHandle = State.CooldownTimer;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        FTimerDelegate::CreateUObject(this, &UNDSkillComponent::OnCooldownFinished, SkillName),
        CoolTime,
        false
    );
}

void UNDSkillComponent::OnCooldownFinished(FName SkillName)
{
    if (FSkillState* State = SkillStates.Find(SkillName))
    {
        State->bIsOnCooldown = false;
        State->CooldownTimer.Invalidate();
        OnSkillCooldownEnd.Broadcast(SkillName);
    }
}