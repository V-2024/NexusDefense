// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDBaseCharacter.h"
#include "Combat/NDCombatComponent.h"
#include "Components/NDAttacksComponent.h"
#include "Components/NDSkillComponent.h"
#include "NDCombatCharacter.generated.h"

class ANDBaseWeapon;

UCLASS()
class NEXUSDEFENSE_API ANDCombatCharacter : public ANDBaseCharacter
{
    GENERATED_BODY()

public:
    ANDCombatCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 전투 관련 함수들
    virtual void HandleAttack(FName SkillName);
    virtual AActor* FindTargetInFront();

    // 입력 처리 함수들
    virtual void PressLMB();
    void ExecuteBasicAttack();
    virtual void PressKeyboard1();
    virtual void PressKeyboard2();
    virtual void PressKeyboard3();
    virtual void PressKeyboard4();

    // 이동 제한
    virtual void MoveForward(float Value) override;
    virtual void MoveRight(float Value) override;

protected:
    // 전투 컴포넌트들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDCombatComponent* CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDAttacksComponent* AttackComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDSkillComponent* SkillComponent;

    // 무기 시스템
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ANDBaseWeapon> WeaponClass;

    UPROPERTY()
    ANDBaseWeapon* Weapon;

    void EquipWeapon();

    // 타겟팅 시스템
    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackTraceRadius = 100.f;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackTraceDistance = 300.f;
};
