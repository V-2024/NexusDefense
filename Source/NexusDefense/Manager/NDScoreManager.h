// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDScoreManager.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	static UNDScoreManager* GetInstance();

	void AddScore(int32 ScoreToAdd);
	void ResetScore();
	int32 GetCurrentScore() const;
	void FinalizeStageScore(int32 StageNumber);

private:
	static UNDScoreManager* Instance;

	int32 CurrentScore;
	TMap<int32, int32> StageScores;

private:
	UNDScoreManager();
};
