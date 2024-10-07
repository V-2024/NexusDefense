// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDStageSelectedGameMode.h"
#include "GameInstance/NDGameInstance.h"

void ANDStageSelectedGameMode::StartPlay()
{
	Super::StartPlay();

	if (!GameInstance)
	{
		// get GameInstance
		GameInstance = Cast<UNDGameInstance>(GetGameInstance());
	}

	UE_LOG(LogTemp, Warning, TEXT("ANDStageSelectedGameMode::StartPlay"));
	GameInstance->TriggerSelectStageEvent();
}

void ANDStageSelectedGameMode::BeginPlay()
{
	Super::BeginPlay();

}

