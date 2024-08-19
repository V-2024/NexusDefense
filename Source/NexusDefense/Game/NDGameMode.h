// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NDGameMode.generated.h"

class ANDGameManager;

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

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddScore(int32 Score);

	UFUNCTION(BlueprintPure, Category = "Game")
	int32 GetCurrentScore() const { return CurrentScore; }

private:
	void InitializeManagers();
	void SubscribeToEvents();
	void UnsubscribeFromEvents();

	UFUNCTION()
	void OnEnemyDefeated(class ANDEnemyBase* DefeatedEnemy);

	UFUNCTION()
	void OnStageCompleted(int32 StageNumber);

	UFUNCTION()
	void OnGameOver();

private:
	UPROPERTY()
	ANDGameManager* GameManager;

	UPROPERTY(EditDefaultsOnly, Category= "Game")
	TSubclassOf<ANDGameManager> GameManagerClass;

	int32 CurrentScore;
};
