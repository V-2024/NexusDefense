// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/NDGameTypes.h"
#include "Manager/NDStageManager.h"
#include "Manager/NDUIManager.h"
#include "Manager/NDSpawnManager.h"
#include "Manager/NDEffectManager.h"
#include "Manager/NDObjectPoolManager.h"
#include "Manager/NDEventManager.h"
#include "Manager/NDDataManager.h"
#include "Manager/NDScoreManager.h"
#include "Manager/NDSoundManager.h"
#include "Manager/NDItemManager.h"
#include "NDGameManager.generated.h"

class ANDStageManager;
class ANDSpawnManager;
class ANDUIManager;
class ANDObjectPoolManager;
class ANDEffectManager;
class ANDObjectPoolManager;
class UNDDataManager;
class UNDEventManager;
class UNDScoreManager;
class UNDSoundManager;
class ANDItemManager;


UCLASS()
class NEXUSDEFENSE_API ANDGameManager : public AActor
{
	GENERATED_BODY()
	
public:
    ANDGameManager();

    static ANDGameManager* GetInstance();

    // Other Manager Access Functions
    FORCEINLINE ANDStageManager*        GetStageManager()       const {     return StageManager;    }
    FORCEINLINE ANDSpawnManager*        GetSpawnManager()       const {     return SpawnManager;    }
    FORCEINLINE ANDUIManager*           GetUIManager()          const {     return UIManager;       }
    FORCEINLINE ANDObjectPoolManager*   GetObjectManager()      const {     return ObjectManager;   }
    FORCEINLINE ANDEffectManager*       GetEffectManager()      const {     return EffectManager;   }
    FORCEINLINE ANDObjectPoolManager*   GetObjectPoolManager()  const {     return ObjectManager;   }
    FORCEINLINE UNDDataManager*         GetDataManager()        const {     return DataManager;     }
    FORCEINLINE UNDEventManager*        GetEventManager()       const {	    return EventManager;    }
    FORCEINLINE UNDScoreManager*        GetScoreManager()       const {     return ScoreManager;    }
    FORCEINLINE UNDSoundManager*        GetSoundManager()       const {     return SoundManager;    }
    FORCEINLINE ANDItemManager*         GetItemManager()        const {     return ItemManager;     }

    FORCEINLINE EGameState              GetGameState()          const {     return CurrentGameState;}
    

    // Manage Game State Functions
    void StartGame();
    void PauseGame();
    void ResumeGame();
    void EndGame();

    void SetGameState(EGameState NewState);
    void SubscribeToEvents();
    void UnsubscribeFromEvents();
    void InitializeManagers(UWorld* World);

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    template<typename T>
    void CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass);

    // Helper Function for CreateManager
    template<typename T>
    typename std::enable_if<std::is_base_of<AActor, T>::value, T*>::type
        CreateManagerInternal(TSubclassOf<T> ManagerClass);

    // Helper Function for CreateManager
    template<typename T>
    typename std::enable_if<!std::is_base_of<AActor, T>::value, T*>::type
        CreateManagerInternal(TSubclassOf<T> ManagerClass);


    void HandleGameStarted();
    void HandleGamePaused();
    void HandleGameResumed();
    void HandleGameOver();
    void HandleStageStarted();

    void CleanupManagers();


protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    


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

    UPROPERTY()
    UNDScoreManager*        ScoreManager;

    UPROPERTY()
    UNDSoundManager*        SoundManager;

    UPROPERTY()
    ANDItemManager*         ItemManager;

    UPROPERTY()
    UWorld*                 GameWorld;
   
    EGameState              CurrentGameState;
};