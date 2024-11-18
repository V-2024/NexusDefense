#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combat/NDCombatComponent.h"
#include "Components/NDExperienceComponent.h"
#include "Components/NDHealthComponent.h"
#include "Interfaces/NDPlayerStatusInterface.h"
#include "NDCharacterWhite.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class NEXUSDEFENSE_API ANDCharacterWhite : public ACharacter, public INDPlayerStatusInterface
{
	GENERATED_BODY()

public:
	ANDCharacterWhite();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �������̽� ����
	virtual void AddExperience(float Amount) override;
	virtual void AddHealth(float Amount) override;

protected:
	virtual void BeginPlay() override;

	// ��ǲ �Լ�
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void PressKeyboard1();
	void PressKeyboard2();
	void PressKeyboard3();
	void PressKeyboard4();

public:
	// ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDExperienceComponent* ExperienceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNDAttacksComponent* AttacksComponent;

};
