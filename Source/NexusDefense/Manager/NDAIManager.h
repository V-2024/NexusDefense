// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AI/NDAIWorker.h"
#include "NDAIManager.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDAIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void RequestAIUpdate(class ANDEnemy* Enemy);
    void ProcessCompletedTasks();

private:
    TSharedPtr<FNDAIWorker> AIWorker;
    FTimerHandle ProcessTasksTimerHandle;
};
