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
    UFUNCTION(BlueprintNativeEvent, Category = "Manager")
    void Initialize();
    virtual void Initialize_Implementation() {}

    UFUNCTION(BlueprintNativeEvent, Category = "Manager")
    void Shutdown();
    virtual void Shutdown_Implementation() {}

    UFUNCTION(BlueprintNativeEvent, Category = "Manager")
    void OnLevelChanged(const FName& NewLevelName);
    virtual void OnLevelChanged_Implementation(const FName& NewLevelName) {}
};
