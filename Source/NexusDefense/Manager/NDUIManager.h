// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/NDGameTypes.h"
#include "NDUIManager.generated.h"


UCLASS()
class NEXUSDEFENSE_API ANDUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDUIManager();

	void UpdateUI(EGameState NewState);

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
	void ShowStageSelectUI();

};
