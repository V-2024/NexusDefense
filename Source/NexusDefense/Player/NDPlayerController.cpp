// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NDPlayerController.h"
#include "Blueprint/UserWidget.h"

void ANDPlayerController::BeginPlay()
{
	Super::BeginPlay();

    //HUD
    if (HUDOverlayAsset)
    {
        HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
        if (HUDOverlay)
        {
            HUDOverlay->AddToViewport();
            HUDOverlay->SetVisibility(ESlateVisibility::Visible);
        }
    }

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void ANDPlayerController::Tick(float DeltaTime)
{
}
