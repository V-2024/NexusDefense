// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDEnemyWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNDEnemyWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEXUSDEFENSE_API INDEnemyWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SetUpEnemyWidget(class UNDUserWidget* Widget) = 0;
};
