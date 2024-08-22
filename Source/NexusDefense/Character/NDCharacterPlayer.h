// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NDCharacterBase.h"
#include "InputActionValue.h"
#include "NDCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCharacterPlayer : public ANDCharacterBase
{
    GENERATED_BODY()

public:
    ANDCharacterPlayer();

public:
    UFUNCTION(BlueprintCallable, Category = "Leveling")
    void GainExperience(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Leveling")
    void LevelUp();

    UFUNCTION(BlueprintPure, Category = "Leveling")
    int32 GetCurrentLevel() const { return CurrentLevel; }

    UFUNCTION(BlueprintPure, Category = "Leveling")
    int32 GetCurrentExperience() const { return CurrentExperience; }

    UFUNCTION(BlueprintPure, Category = "Leveling")
    int32 GetExperienceRequiredForNextLevel() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    int32 CurrentLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    int32 CurrentExperience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    int32 MaxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    int32 BaseExperienceRequirement;

protected:
    virtual void Attack() override;
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UCameraComponent> FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UInputAction> AttackAction;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
};