// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDGameManager.generated.h"

class ANDStageManager;
class ANDSpawnManager;
class ANDUIManager;
class ANDObjectPoolManager;
class ANDEffectManager;

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Ready,
    Playing,
    Paused,
    GameOver
};

UCLASS()
class NEXUSDEFENSE_API ANDGameManager : public AActor
{
	GENERATED_BODY()
	
public:
    ANDGameManager();

    static ANDGameManager* GetInstance();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Other Manager Access Functions
    ANDStageManager*        GetStageManager()       const { return StageManager; }
    ANDSpawnManager*        GetSpawnManager()       const { return SpawnManager; }
    ANDUIManager*           GetUIManager()          const { return UIManager; }
    ANDObjectPoolManager*   GetObjectManager()      const { return ObjectManager; }
    ANDEffectManager*       GetEffectManager()      const { return EffectManager; }

    EGameState              GetGameState()          const { return CurrentGameState; }

    // Manage Game State Functions
    void StartGame();
    void PauseGame();
    void ResumeGame();
    void EndGame();


private:
    void InitializeManagers();

    template<typename T>
    void CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass);


private:
    static ANDGameManager*  Instance;

    UPROPERTY()
    ANDStageManager*        StageManager;

    UPROPERTY()
    ANDSpawnManager*        SpawnManager;

    UPROPERTY()
    ANDUIManager*           UIManager;

    UPROPERTY()
    ANDObjectPoolManager*   ObjectManager;

    UPROPERTY()
    ANDEffectManager*       EffectManager;

    EGameState              CurrentGameState;
};