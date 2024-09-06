// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDGameMode.h"
#include "Enemy/NDEnemyBase.h"
#include "Manager/NDEventManager.h"
#include "GameInstance/NDGameInstance.h"

ANDGameMode::ANDGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANDGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartGame();
}

void ANDGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
}


void ANDGameMode::StartGame()
{
	UNDEventManager::GetInstance()->TriggerGameStarted();
}