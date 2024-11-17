#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageSystem/ND_C_DamageSystem.h"
//#include "Components/NDAttacksComponent.h"

#include "Interfaces/NDPlayerStatusInterface.h"
#include "Components/NDExperienceComponent.h"
#include "Components/NDHealthComponent.h"
#include "NDCharacterWhite.generated.h"

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	None,
	Attack1,
	Attack2,
	Attack3,
	Attack4
};

UCLASS()
class NEXUSDEFENSE_API ANDCharacterWhite : public ACharacter, public INDPlayerStatusInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDCharacterWhite();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

	// NDPlayerStatueInterface 가상함수 구현
	virtual void AddExperience(float Amount) override;
	virtual void AddHealth(float Amount) override;

    // 인풋 바인딩
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDExperienceComponent* ExperienceComponent;

	// 공격
	void InputAttack1();
	void InputAttack2();
	void InputAttack3();
	void InputAttack4();

	// 자식에서 공격 실행에 사용하는거임
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void ExecuteAttack(EAttackType AttackType);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bAttacking;

	// 현재 공격 종류
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	EAttackType CurrentAttackType;

	// 스탯
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
};
