// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NDStageSelectedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDStageSelectedGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UNDGameInstance* GameInstance;
};
