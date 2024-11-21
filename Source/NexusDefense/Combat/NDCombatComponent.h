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
    // 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillExecuted OnSkillExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnCooldownEnd OnCooldownEnd;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void NotifySkillEnd();

    // 스킬 실행 함수
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteSkill(FName SkillName);

    // 스킬 상태 확인 함수
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

    // 콤보 관련 함수
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessComboCommand();

protected:
    // 데이터 테이블 참조
    UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowedClasses = "DataTable"))
    TSoftObjectPtr<UDataTable> SkillDataTable;

    // 상태 변수들
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TMap<FName, FSkillState> SkillStates;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    ECombatState CurrentState;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    FName CurrentSkillName;

    // 콤보 관련 변수
    UPROPERTY()
    int32 CurrentCombo = 0;

    UPROPERTY()
    bool HasNextComboCommand = false;

    FTimerHandle ComboTimerHandle;

    // 콤보 데이터
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

    // 콤보 관련 함수들
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


    // 내부 유틸리티 함수
    void StartCooldown(FName SkillName, float CoolTime);
    UFUNCTION()
    void OnCooldownFinished(FName SkillName);
};

