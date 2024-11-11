// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
