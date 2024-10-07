// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Types/NDGameTypes.h"
#include "NDUIManager.generated.h"

class UNDMainMenuWidget;
class UNDPauseMenuWidget;
class UNDGameUIWidget;
class UNDGameOverUIWidget;
class UNDStageSelectWidget;

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

	FORCEINLINE UNDMainMenuWidget* GetMainMenuWidget() const { return MainMenuWidget; }
	FORCEINLINE UNDPauseMenuWidget* GetPauseMenuWidget() const { return PauseMenuWidget; }
	FORCEINLINE UNDGameUIWidget* GetGameUIWidget() const { return GameUIWidget; }
	FORCEINLINE UNDGameOverUIWidget* GetGameOverUIWidget() const { return GameOverUIWidget; }
	FORCEINLINE UNDStageSelectWidget* GetStageSelectWidget() const { return StageSelectWidget; }

private:
	void CreateWidgets();
	void ShowMainMenu();
	void ShowPauseMenu();
	void ShowGameUI();
	void ShowGameOverUI();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNDMainMenuWidget>		MainMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNDPauseMenuWidget>		PauseMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNDGameUIWidget>			GameUIWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNDGameOverUIWidget>		GameOverUIWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNDStageSelectWidget>		StageSelectUIWidgetClass;


	UNDMainMenuWidget*							MainMenuWidget;

	UNDPauseMenuWidget*							PauseMenuWidget;

	UNDGameUIWidget*							GameUIWidget;

	UNDGameOverUIWidget*						GameOverUIWidget;

	UNDStageSelectWidget*						StageSelectWidget;
};
