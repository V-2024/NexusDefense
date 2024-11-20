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

    // ������ ���̺� ����
    UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowedClasses = "DataTable"))
    TSoftObjectPtr<UDataTable> SkillDataTable;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessAttackHit();

protected:

    // ���� ������
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TMap<FName, FSkillState> SkillStates;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    ECombatState CurrentState;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    FName CurrentSkillName;

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

