// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDBaseCharacter.h"
#include "Combat/NDCombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NDCombatCharacter.generated.h"

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

	// Input ó�� virtual �Լ���
	virtual void PressKeyboard1();
	virtual void PressKeyboard2();
	virtual void PressKeyboard3();
	virtual void PressKeyboard4();

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

protected:
	// ���� ������Ʈ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	UNDCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	UNDAttacksComponent* AttacksComponent;
	
	// ���� Ȯ�ο�
	bool bIsAttacking;
	UFUNCTION()
	void OnAttackEnd();

	// Ÿ���� Trace
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackTraceRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackTraceDistance = 300.f;

	UPROPERTY()
	AActor* SubTarget;

	AActor* FindTargetInFront();
};
