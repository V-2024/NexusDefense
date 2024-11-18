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
	// 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UNDAttacksComponent* AttacksComponent;

	// 공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage4;

	// 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackLength = 200.0f;

	// 노티파이 호출 함수
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ProcessAttack(EAttackType AttackType);

	// 데미지 정보 설정 함수
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual FND_S_DamageInfo GetAttackDamageInfo(EAttackType AttackType) const;

	// 공격 몽타주 가져오기
	UFUNCTION(BlueprintCallable, Category = "Combat")
	UAnimMontage* GetAttackMontage(EAttackType AttackType) const;

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:
	// 현재 공격의 데미지 정보를 담는 변수
	FND_S_DamageInfo CurrentAttackDamageInfo;
};
