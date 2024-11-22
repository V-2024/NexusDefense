
#pragma once

#include "CoreMinimal.h"
#include "Character/NDCombatCharacter.h"
#include "NDCombatCharacterFighter.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDCombatCharacterFighter : public ANDCombatCharacter
{
	GENERATED_BODY()
	
public:
	ANDCombatCharacterFighter();

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ProcessAttackHit();

protected:
	virtual void BeginPlay() override;

	virtual void PressLMB() override;
	virtual void PressKeyboard1() override;
	virtual void PressKeyboard2() override;
	virtual void PressKeyboard3() override;
	virtual void PressKeyboard4() override;

	// 고유 기능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNDComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool hasNextComboCommand = false;
};
