#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NDCombatTypes.h"
#include "Animation/AnimMontage.h"
#include "NDComboComponent.generated.h"

class UNDCombatComponent;
class UNDAttacksComponent;
class UNDComboActionData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboUpdated, int32, NewComboCount);

UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDComboComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNDComboComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessComboCommand();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessAttackHit();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetComboData(UNDComboActionData* NewComboData) { ComboActionData = NewComboData; }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetComboMontage(UAnimMontage* NewMontage) { ComboActionMontage = NewMontage; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    int32 GetCurrentCombo() const { return CurrentCombo; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<UNDComboActionData> ComboActionData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TObjectPtr<UAnimMontage> ComboActionMontage;

    UPROPERTY()
    int32 CurrentCombo;

    FTimerHandle ComboTimerHandle;
    bool hasNextComboCommand;

    void ComboActionBegin();
    void ComboActionEnd(UAnimMontage* Montage, bool bInterrupted);
    void SetComboCheckTimer();
    void ComboCheck();

    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    UPROPERTY()
    UNDCombatComponent* CombatComponent;

    UPROPERTY()
    UNDAttacksComponent* AttacksComponent;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnComboUpdated OnComboUpdated;
};

