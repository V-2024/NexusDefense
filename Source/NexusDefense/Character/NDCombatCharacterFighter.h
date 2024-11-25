
#pragma once

#include "CoreMinimal.h"
#include "Character/NDCombatCharacter.h"
#include "Components/NDComboComponent.h"
#include "NDCombatCharacterFighter.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDCombatCharacterFighter : public ANDCombatCharacter
{
    GENERATED_BODY()

public:
    ANDCombatCharacterFighter();

protected:
    virtual void BeginPlay() override;

    // 전투 입력 처리 오버라이드
    virtual void PressLMB() override;
    virtual void PressKeyboard1() override;
    virtual void PressKeyboard2() override;
    virtual void PressKeyboard3() override;
    virtual void PressKeyboard4() override;

    // 콤보 시스템
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
    UNDComboComponent* ComboComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TObjectPtr<UAnimMontage> ComboActionMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
    TObjectPtr<class UNDComboActionData> ComboActionData;
};