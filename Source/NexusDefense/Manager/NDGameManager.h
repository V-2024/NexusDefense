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
class ANDObjectPoolManager;
class UNDDataManager;
class UNDEventManager;

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
    ANDStageManager*        GetStageManager()       const {     return StageManager;    }
    ANDSpawnManager*        GetSpawnManager()       const {     return SpawnManager;    }
    ANDUIManager*           GetUIManager()          const {     return UIManager;       }
    ANDObjectPoolManager*   GetObjectManager()      const {     return ObjectManager;   }
    ANDEffectManager*       GetEffectManager()      const {     return EffectManager;   }
    ANDObjectPoolManager*   GetObjectPoolManager()  const {     return ObjectManager;   }
    UNDDataManager*         GetDataManager()        const {     return DataManager;     }
    UNDEventManager*        GetEventManager()       const {	    return EventManager;    }  

    EGameState              GetGameState()          const { return CurrentGameState; }

    // Manage Game State Functions
    void StartGame();
    void PauseGame();
    void ResumeGame();
    void EndGame();

    void SubscribeToEvents();
    void UnsubscribeFromEvents();


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

    UPROPERTY()
    ANDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    UNDDataManager*         DataManager;

    UPROPERTY()
    UNDEventManager*        EventManager;

   
    EGameState              CurrentGameState;
};