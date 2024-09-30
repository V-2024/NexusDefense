// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FPlanetInfo.h"
#include "NDPlanetDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDPlanetDetailWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlanetInfo(const FPlanetInfo& InPlanetInfo);

	UFUNCTION(BlueprintImplementableEvent, Category = "Planet")
	void OnPlanetInfoUpdated();

protected:
	virtual void NativeConstruct() override;

private:
	void UpdateStageButtons();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Planet")
	FPlanetInfo PlanetInfo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* PlanetDetailImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlanetNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlanetDescriptionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* StageButtonContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Planet")
	TSubclassOf<class UNDStageButtonWidget> StageButtonWidgetClass;
};
