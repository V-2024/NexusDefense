// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/NDGameTypes.h"
#include "NDUIManager.generated.h"

class UNDMainMenuWidget;
class UNDPauseMenuWidget;
class UNDGameUIWidget;
class UNDGameOverUIWidget;
class UNDStageSelectWidget;

UCLASS()
class NEXUSDEFENSE_API ANDUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDUIManager();

	// get instance
	FORCEINLINE static ANDUIManager* GetInstance() { return Instance; }

	void StartUI();
	void UpdateUI(EGameState NewState);

	
	void ShowStageSelectUI();

	void CloseMainMenu();
	void ClosePauseMenu();
	void CloseGameUI();
	void CloseGameOverUI();
	void CloseStageSelectUI();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

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

	static ANDUIManager*						Instance;
};
