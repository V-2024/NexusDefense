// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Stages/FPlanetinfo.h"
#include "NDStageSelectWidget.generated.h"


class UNDPlanetWidget;
class UNDPlanetDetailWidget;
class UNDGameInstance;
class UNDStageManager;

UCLASS()
class NEXUSDEFENSE_API UNDStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void SelectPlanet(int32 PlanetIndex);

	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void OnBackButtonClicked();

	void OnPlanetClicked(int32 PlanetIndex);

private:
	void InitializePlanets();
	void UpdatePlanetStates();

	void ZoomToPlanet(int32 PlanetIndex);
	void ZoomOutToPlanets();
	void BackToMainMenu();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* StarSystemCanvas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Planet", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UNDPlanetWidget> PlanetWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UNDPlanetWidget*> PlanetWidgets;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UNDPlanetDetailWidget* PlanetDetailWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TotalScoreText;

private:
	//UPROPERTY()
	//class UNDGameInstance* GameInstance;

	UPROPERTY()
	class UNDStageManager* StageManager;

	UPROPERTY()
	TArray<FPlanetInfo>     PlanetInfos;

	int32 CurrentSelectedPlanetIndex;
	bool bIsZoomedIn = false;
};
