// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NDCombatTypes.h"
#include "Combat/NDCombatData.h"
#include "Components/NDAttacksComponent.h"
#include "NDCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillExecuted, FName, SkillName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCooldownEnd, FName, SkillName);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNDCombatComponent();

protected:
    virtual void BeginPlay() override;

public:
    // ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillExecuted OnSkillExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnCooldownEnd OnCooldownEnd;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void NotifySkillEnd();

    // ��ų ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteSkill(FName SkillName);

    // ��ų ���� Ȯ�� �Լ�
    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsSkillReady(FName SkillName) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetSkillCooldownRemaining(FName SkillName) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    ECombatState GetCurrentState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    FName GetCurrentSkillName() const { return CurrentSkillName; }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessAttackHit();

    // �޺� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessComboCommand();

protected:
    // ������ ���̺� ����
    UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowedClasses = "DataTable"))
    TSoftObjectPtr<UDataTable> SkillDataTable;

    // ���� ������
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TMap<FName, FSkillState> SkillStates;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    ECombatState CurrentState;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    FName CurrentSkillName;

    // �޺� ���� ����
    UPROPERTY()
    int32 CurrentCombo = 0;

    UPROPERTY()
    bool HasNextComboCommand = false;

    FTimerHandle ComboTimerHandle;

    // �޺� ������
    UPROPERTY(EditDefaultsOnly, Category = "Combat|Combo")
    UAnimMontage* ComboActionMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Combo")
    TArray<float> EffectiveFrameCount;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Combo")
    float FrameRate = 30.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Combo")
    int32 MaxComboCount = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Combo")
    FString MontageSectionNamePrefix = "Attack";

    // �޺� ���� �Լ���
    void ComboActionBegin();
    void ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded);
    void SetComboCheckTimer();
    void ComboCheck();

private:
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    UPROPERTY()
    UNDAttacksComponent* AttacksComponent;

    FCombatSkillData* CurrentSkillData;


    // ���� ��ƿ��Ƽ �Լ�
    void StartCooldown(FName SkillName, float CoolTime);
    UFUNCTION()
    void OnCooldownFinished(FName SkillName);
};

