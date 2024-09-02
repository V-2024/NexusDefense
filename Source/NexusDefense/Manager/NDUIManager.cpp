// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDUIManager.h"
#include "Manager/NDEventManager.h"


ANDUIManager::ANDUIManager()
{

}

void ANDUIManager::UpdateUI(EGameState NewState)
{
	switch (NewState)
	{
		case EGameState::Ready:
			ShowMainMenu();
			break;
		case EGameState::Playing:
			ShowGameUI();
			break;
		case EGameState::Paused:
			ShowPauseMenu();
			break;
		case EGameState::GameOver:
			ShowGameOverUI();
			break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void ANDUIManager::BeginPlay()
{
	Super::BeginPlay();
	//CreateWidgets();
	UNDEventManager::GetInstance()->TriggerUIInitialized();
}

// Called every frame
void ANDUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDUIManager::CreateWidgets()
{

}

void ANDUIManager::ShowMainMenu()
{

}

void ANDUIManager::ShowPauseMenu()
{

}

void ANDUIManager::ShowGameUI()
{

}

void ANDUIManager::ShowGameOverUI()
{

}

void ANDUIManager::ShowStageSelectUI()
{

}