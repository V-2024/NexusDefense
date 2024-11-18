// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterWhite.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "Components/NDAttacksComponent.h"
#include "NDCharacterWhiteSkilled.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterWhiteSkilled : public ANDCharacterWhite
{
	GENERATED_BODY()
	
public:
	ANDCharacterWhiteSkilled();

	virtual void ExecuteAttack(EAttackType AttackType) override;

protected:
	// ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UNDAttacksComponent* AttacksComponent;

	// ���� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage4;

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackLength = 200.0f;

	// ��Ƽ���� ȣ�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ProcessAttack(EAttackType AttackType);

	// ������ ���� ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual FND_S_DamageInfo GetAttackDamageInfo(EAttackType AttackType) const;

	// ���� ��Ÿ�� ��������
	UFUNCTION(BlueprintCallable, Category = "Combat")
	UAnimMontage* GetAttackMontage(EAttackType AttackType) const;

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:
	// ���� ������ ������ ������ ��� ����
	FND_S_DamageInfo CurrentAttackDamageInfo;
};
