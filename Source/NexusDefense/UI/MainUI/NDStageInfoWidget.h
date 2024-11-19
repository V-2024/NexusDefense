// NDStageInfoWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FStageInfo.h"
#include "NDStageInfoWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UOverlay;

UCLASS()
class NEXUSDEFENSE_API UNDStageInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* StageIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StageNameText;

	UPROPERTY(meta = (BindWidget))
	UButton* StageButton;

	UPROPERTY(meta = (BindWidget))
	UOverlay* LockOverlay;

	UPROPERTY(meta = (BindWidget))
	UImage* ClearedIcon;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverAnimation;

public:
	void SetStageInfo(const FStageInfo& InStageInfo);
	void UpdateLockStatus(bool bIsUnlocked);
	void UpdateClearedStatus(bool bIsCleared);

private:
	UPROPERTY()
	FStageInfo StageInfo;

	UFUNCTION()
	void OnStageButtonClicked();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnhovered();

	void UpdateVisuals();
};