// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NDStartLevelGameMode.generated.h"

class UNDGameInstance;


UCLASS()
class NEXUSDEFENSE_API ANDStartLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	UNDGameInstance* GameInstance;
};
