// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDStageSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void SelectStage(int32 StageIndex);

	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void BackToMainMenu();

private:
	void UpdateStageInfo();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TArray<class UButton*> StageButtons;

	UPROPERTY()
	class UButton* BackButton;
};
