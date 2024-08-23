// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NDSaveGame.generated.h"


UCLASS()
class NEXUSDEFENSE_API UNDSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY()
    int32 PlayerScore;

    UPROPERTY()
    int32 CurrentLevel;

    UPROPERTY()
    TArray<int32> UnlockedStages;
};
