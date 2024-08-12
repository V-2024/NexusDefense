// Fill out your copyright notice in the Description page of Project Settings.


#include "Stages/NDStage.h"
#include "Manager/NDGameManager.h"
#include "Manager/NDSpawnManager.h"


ANDStage::ANDStage()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentWave = 0;
	RemainingEnemies = 0;
	bIsStageActive = false;
}

void ANDStage::Initialize(UStageData* InStageData)
{
	StageData = InStageData;
}

void ANDStage::StartStage()
{
	if (!StageData)
	{
		UE_LOG(LogTemp, Error, TEXT("StageData is not set!"));
		return;
	}

	bIsStageActive = true;
	CurrentWave = 0;
	StartNextWave();
}

void ANDStage::EndStage()
{
	bIsStageActive = false;

	// Add end stage rogic
}

bool ANDStage::IsStageCleared() const
{
	return CurrentWave >= StageData->Waves.Num() && RemainingEnemies == 0;
}

void ANDStage::OnEnemyDefeated()
{
	RemainingEnemies--;

	if (RemainingEnemies <= 0)
	{
		CheckWaveCompletion();
	}
}

void ANDStage::StartNextWave()
{
	if (CurrentWave >= StageData->Waves.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("No more waves to start!"));
		return;
	}

	RemainingEnemies = StageData->Waves[CurrentWave].EnemyCount;
	ANDSpawnManager* SpawnManager = ANDGameManager::GetInstance()->GetSpawnManager();

	if (SpawnManager)
	{
		SpawnManager->StartSpawning(this, StageData->Waves[CurrentWave]);
	}
}

void ANDStage::CheckWaveCompletion()
{
	CurrentWave++;

	if (CurrentWave < StageData->Waves.Num())
	{
		StartNextWave();
	}
	else
	{
		EndStage();
	}
}


