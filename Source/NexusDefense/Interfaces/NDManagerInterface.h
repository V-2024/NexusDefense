// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDManagerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNDManagerInterface : public UInterface
{
    GENERATED_BODY()
};

class NEXUSDEFENSE_API INDManagerInterface
{
    GENERATED_BODY()

public:
    virtual void Initialize_Implementation() {}
    virtual void Shutdown_Implementation() {}
    virtual void OnLevelChanged_Implementation(const FName& NewLevelName) {}
};
