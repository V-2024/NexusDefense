// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "NDStageSelectWidget.generated.h"


class UNDPlanetWidget;
class UNDPlanetDetailWidget;
class UNDGameInstance;

UCLASS()
class NEXUSDEFENSE_API UNDStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void SelectPlanet(int32 PlanetIndex);

	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void BackToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void ZoomToPlanet(int32 PlanetIndex);

	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void ZoomOutToPlanets();

private:
	void InitializePlanets();
	void UpdatePlanetStates();

	UFUNCTION()
	void OnBackButtonClicked();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* StarSystemCanvas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TSubclassOf<class UNDPlanetWidget> PlanetWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TArray<class UNDPlanetWidget*> PlanetWidgets;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UNDPlanetDetailWidget* PlanetDetailWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TotalScoreText;

private:
	UPROPERTY()
	class UNDGameInstance* GameInstance;

	int32 CurrentSelectedPlanetIndex;
	bool bIsZoomedIn = false;
};
