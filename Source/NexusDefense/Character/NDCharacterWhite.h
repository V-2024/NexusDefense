#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageSystem/ND_C_DamageSystem.h"
//#include "Components/NDAttacksComponent.h"
#include "Components/NDHealthComponent.h"
//����� ��ƼŬ
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
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
class NEXUSDEFENSE_API ANDCharacterWhite : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDCharacterWhite();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ��ǲ �Լ� (���Ŀ� ���� �߰�)
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

	// ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UNDHealthComponent* HealthComponent;

	// ü�� ���� ��������Ʈ�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void OnHealthChanged(float NewHealth);

	// ����
	void InputAttack1();
	void InputAttack2();
	void InputAttack3();
	void InputAttack4();

	// �ڽĿ��� ���� ���࿡ ����ϴ°���
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void ExecuteAttack(EAttackType AttackType);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bAttacking;

	// ���� ���� ����
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	EAttackType CurrentAttackType;

	// ����
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

	// ȿ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	USoundCue* HealSound;
	// ��ƼŬ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* HealEffect;
};
