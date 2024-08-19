// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDScoreManager.h"

UNDScoreManager* UNDScoreManager::Instance = nullptr;

UNDScoreManager* UNDScoreManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UNDScoreManager>();
		Instance->AddToRoot();
	}

	return Instance;
}

void UNDScoreManager::AddScore(int32 ScoreToAdd)
{
	CurrentScore += ScoreToAdd;
}

void UNDScoreManager::ResetScore()
{
	CurrentScore = 0;
	StageScores.Empty();
}

int32 UNDScoreManager::GetCurrentScore() const
{
	return CurrentScore;
}

void UNDScoreManager::FinalizeStageScore(int32 StageNumber)
{
	StageScores.Add(StageNumber, CurrentScore);
	//UNDDataManager::GetInstance()->SaveStageScore(StageNumber, CurrentScore);
	//UNDEventManager::GetInstance()->BroadcastStageScoreFinalized(StageNumber, CurrentScore);
}

UNDScoreManager::UNDScoreManager() : CurrentScore(0)
{
}

