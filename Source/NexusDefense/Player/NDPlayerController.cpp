// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NDPlayerController.h"

void ANDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
