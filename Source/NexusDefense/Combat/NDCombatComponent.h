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
    // 델리게이트 함수
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillExecuted OnSkillExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnCooldownEnd OnCooldownEnd;

    // 노티파이 함수
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void NotifySkillEnd();

    // 스킬 관련 함수
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteSkill(FName SkillName);

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

    // 데이터 테이블 가져오기
    UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowedClasses = "DataTable"))
    TSoftObjectPtr<UDataTable> SkillDataTable;

    // 상태 변수
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    ECombatState CurrentState;
protected:

    // 상태 변수들
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TMap<FName, FSkillState> SkillStates;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    FName CurrentSkillName;

private:
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    UPROPERTY()
    UNDAttacksComponent* AttacksComponent;

    FCombatSkillData* CurrentSkillData;


    // 유틸리티 함수들
    void StartCooldown(FName SkillName, float CoolTime);
    UFUNCTION()
    void OnCooldownFinished(FName SkillName);
};

