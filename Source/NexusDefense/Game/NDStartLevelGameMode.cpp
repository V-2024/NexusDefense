// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDStartLevelGameMode.h"
#include "GameInstance/NDGameInstance.h"

void ANDStartLevelGameMode::StartPlay()
{
	Super::StartPlay();

	if (!GameInstance)
	{
		GameInstance = Cast<UNDGameInstance>(GetGameInstance());
	}

	
	if (GameInstance)
	{
		//GameInstance->TriggerGameStartedEvent();
	}
}

void ANDStartLevelGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}
