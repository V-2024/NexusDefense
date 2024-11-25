// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/NDExperienceComponent.h"
#include "Components/NDHealthComponent.h"
#include "Interfaces/NDPlayerStatusInterface.h"
#include "NDBaseCharacter.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDBaseCharacter : public ACharacter, public INDPlayerStatusInterface
{
    GENERATED_BODY()

public:
    ANDBaseCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // �������̽� ����
    virtual void AddExperience(float Amount) override;
    virtual void AddHealth(float Amount) override;

protected:
    virtual void BeginPlay() override;

    // �̵� �Լ�
    virtual void MoveForward(float Value);
    virtual void MoveRight(float Value);
    virtual void Turn(float Value);
    virtual void LookUp(float Value);

protected:
    // ������Ʈ��
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UNDHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UNDExperienceComponent* ExperienceComponent;
};