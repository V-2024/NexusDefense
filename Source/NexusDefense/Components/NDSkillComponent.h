
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NDCombatTypes.h"
#include "Combat/NDCombatData.h"
#include "NDSkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillExecuted, FName, SkillName, float, CoolTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillCooldownEnd, FName, SkillName);

UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNDSkillComponent();

    // ��ų ���� ���� �Լ���
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteSkill(FName SkillName);

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsSkillReady(FName SkillName) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetSkillCooldownRemaining(FName SkillName) const;

protected:
    virtual void BeginPlay() override;

    // ��ų ������ ���̺� ����
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSoftObjectPtr<UDataTable> SkillDataTable;

    // ��ų ���� ��
    UPROPERTY()
    TMap<FName, FSkillState> SkillStates;

    // ������Ʈ ���۷�����
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    UPROPERTY()
    class UNDCombatComponent* CombatComponent;

    UPROPERTY()
    class UNDAttacksComponent* AttacksComponent;

    // �̺�Ʈ ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillExecuted OnSkillExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillCooldownEnd OnSkillCooldownEnd;

private:
    // ��ٿ� ���� �Լ���
    void StartCooldown(FName SkillName, float CoolTime);

    UFUNCTION()
    void OnCooldownFinished(FName SkillName);
};

