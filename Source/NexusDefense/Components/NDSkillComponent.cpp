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

    // 필요한 컴포넌트들 찾기
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

    // 현재 스킬 사용 가능 상태인지 확인
    if (CombatComponent->GetCurrentState() != ECombatState::None)
    {
        return false;
    }

    // 스킬 데이터 로드
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

    // 쿨다운 체크
    if (!IsSkillReady(SkillName))
    {
        return false;
    }

    // 스킬 실행
    if (UAnimMontage* Montage = SkillData->SkillMontage.LoadSynchronous())
    {
        OwnerCharacter->PlayAnimMontage(Montage);
        CombatComponent->SetCurrentState(ECombatState::Attacking);

        // 쿨다운 시작
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

    // 쿨다운 타이머 설정
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