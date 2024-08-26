// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDCharacterBase.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ANDCharacterBase();

    void SetComponents();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
    TObjectPtr<class UAnimMontage> ComboActionMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UNDComboActionData> ComboActionData;

    virtual void Attack();
    void ProcessComboCommand();
    void ComboActionBegin();
    void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
    void SetComboCheckTimer();
    void ComboCheck();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    float MovementSpeed;

// Stat
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UND_C_DamageSystem> DamageableComponent;

// UI Widget
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> HPBarWidget;


private:
    int32 CurrentCombo = 0;
    FTimerHandle ComboTimerHandle;
    bool HasNextComboCommand = false;
};
