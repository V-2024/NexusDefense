// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Types/NDGameTypes.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FPlanetInfo.h"
#include "Stages/FStageInfo.h"
#include "NDUIManager.generated.h"

class UNDPlanetOverviewWidget;
class UNDStageInfoWidget;

UCLASS()
class NEXUSDEFENSE_API UNDUIManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UNDUIManager();

	UFUNCTION()
	void StartUI();
	UFUNCTION()
	void UpdateUI(EGameState NewState);

	
	void ShowStageSelectUI();

	void CloseMainMenu();
	void ClosePauseMenu();
	void CloseGameUI();
	void CloseGameOverUI();
	void CloseStageSelectUI();
	void OnPlanetClicked(int32 PlanetIndex);

private:
	void CreateWidgets();
	void ShowMainMenu();
	void ShowPauseMenu();
	void ShowGameUI();
	void ShowGameOverUI();

	void ShowPlanetOverview();
	void ShowPlanetDetail(const FPlanetInfo& PlanetInfo);
	void UpdateStageInfo(const FStageInfo& StageInfo);
	void HandlePlanetZoomIn(const FPlanetInfo& PlanetInfo);
	void HandlePlanetZoomOut();

private:
	UPROPERTY(Transient)
	class UNDPlanetOverviewWidget* PlanetOverviewWidget;
    
	UPROPERTY(Transient)
	class UNDPlanetDetailWidget* PlanetDetailWidget;
    
	UPROPERTY(Transient)
	class UNDStageInfoWidget* StageInfoWidget;

	// Navigation state
	FPlanetInfo CurrentPlanetInfo;
	FStageInfo CurrentStageInfo;
	bool bIsInPlanetView;
};
