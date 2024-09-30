// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FStageInfo.h"
#include "Components/Button.h"
#include "NDStageButtonWidget.generated.h"


UCLASS()
class NEXUSDEFENSE_API UNDStageButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetStageID(int32 Index);
	void SetStageInfo(const FStageInfo& Info);
	void UpdateStageState();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stage")
	void OnStageInfoUpdated();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStageButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Stage")
	int32 StageID;

	UPROPERTY(BlueprintReadOnly, Category = "Stage")
	FStageInfo StageInfo;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StageButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StageNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* StageIcon;

private:
	UPROPERTY()
	//class UNDGameInstance* GameInstance;

	bool bIsUnlocked = false;
};
