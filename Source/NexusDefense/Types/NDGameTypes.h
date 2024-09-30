// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Ready UMETA(DisplayName = "Ready"),
    Playing UMETA(DisplayName = "Playing"),
    Paused UMETA(DisplayName = "Paused"),
    StageSelect UMETA(DisplayName = "StageSelect"),
    GameOver UMETA(DisplayName = "GameOver")
};
