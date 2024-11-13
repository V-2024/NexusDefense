// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/NDDamageableInterface.h"
#include "DamageSystem/ND_C_DamageSystem.h"
#include "Components/NDAttacksComponent.h"
#include "NDCharacterWhite.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class NEXUSDEFENSE_API ANDCharacterWhite : public ACharacter, public INDDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDCharacterWhite();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 인풋 함수 (추후에 점프 추가)
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// 공격
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	//스탯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	UAnimMontage* CombatMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Experience;

	// NDDamageableInterface 함수들
	virtual bool TakeDamage(const FS_DamageInfo& DamageInfo) override;
	virtual float GetHealth() const override { return Health; }
	virtual float GetMaxHealth() const override { return MaxHealth; }
	virtual bool IsDead() const override { return Health > 0; }

	//공격 애니메이션 노티파이 처리를 위한 함수
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackMontageNotifyBegin(FName NotifyName);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackMontageNotifyEnd(FName NotifyName);

protected:

	// DamageSystem 추가
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UND_C_DamageSystem* DamageSystem;

	// Attacks 추가
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UNDAttacksComponent* AttacksComponent;

	// 데미지 이벤트 처리 함수
	UFUNCTION()
	void OnDamageReceived(float DamageAmount);

	UFUNCTION()
	void OnDeathReceived();
};
