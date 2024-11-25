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

    // ���� ���� �Լ���
    virtual void HandleAttack(FName SkillName);
    virtual AActor* FindTargetInFront();

    // �Է� ó�� �Լ���
    virtual void PressLMB();
    void ExecuteBasicAttack();
    virtual void PressKeyboard1();
    virtual void PressKeyboard2();
    virtual void PressKeyboard3();
    virtual void PressKeyboard4();

    // �̵� ����
    virtual void MoveForward(float Value) override;
    virtual void MoveRight(float Value) override;

protected:
    // ���� ������Ʈ��
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDCombatComponent* CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDAttacksComponent* AttackComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDSkillComponent* SkillComponent;

    // ���� �ý���
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ANDBaseWeapon> WeaponClass;

    UPROPERTY()
    ANDBaseWeapon* Weapon;

    void EquipWeapon();

    // Ÿ���� �ý���
    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackTraceRadius = 100.f;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackTraceDistance = 300.f;
};
