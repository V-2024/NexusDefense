// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NDGameMode.generated.h"

class UNDUIManager;

UCLASS()
class NEXUSDEFENSE_API ANDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANDGameMode();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();


private:

};
