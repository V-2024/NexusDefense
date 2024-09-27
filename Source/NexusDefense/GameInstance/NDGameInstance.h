// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Types/NDGameTypes.h"
#include "NDGameInstance.generated.h"

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
class NEXUSDEFENSE_API UNDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UNDGameInstance();
	virtual void Init() override;

    // Other Manager Access Functions
    FORCEINLINE ANDStageManager* GetStageManager()       const { return StageManager; }
    FORCEINLINE ANDSpawnManager* GetSpawnManager()       const { return SpawnManager; }
    FORCEINLINE ANDUIManager* GetUIManager()          const { return UIManager; }
    FORCEINLINE ANDObjectPoolManager* GetObjectManager()      const { return ObjectManager; }
    FORCEINLINE ANDEffectManager* GetEffectManager()      const { return EffectManager; }
    FORCEINLINE ANDObjectPoolManager* GetObjectPoolManager()  const { return ObjectManager; }
    FORCEINLINE UNDDataManager* GetDataManager()        const { return DataManager; }
    FORCEINLINE UNDEventManager* GetEventManager()       const { return EventManager; }
    FORCEINLINE UNDScoreManager* GetScoreManager()       const { return ScoreManager; }
    FORCEINLINE UNDSoundManager* GetSoundManager()       const { return SoundManager; }
    FORCEINLINE ANDItemManager* GetItemManager()        const { return ItemManager; }
    FORCEINLINE EGameState              GetGameState()          const { return CurrentGameState; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    void ChangeGameModeForLevel(const FName& LevelName);
   
    void SetGameState(EGameState NewState);
    void SubscribeToEvents();
    void UnsubscribeFromEvents();
    void InitializeManagers();

    // event handeling level changed
    void OnLevelChanged(const FName& LevelName);

private:
    template<typename T>
    void CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass, FName ManagerName);

    // Helper Function for CreateManager
    template<typename T>
    typename std::enable_if<std::is_base_of<AActor, T>::value, T*>::type
        CreateManagerInternal(TSubclassOf<T> ManagerClass, FName ManagerName);

    // Helper Function for CreateManager
    template<typename T>
    typename std::enable_if<!std::is_base_of<AActor, T>::value, T*>::type
        CreateManagerInternal(TSubclassOf<T> ManagerClass, FName ManagerName);

    void StartGame();
    void CheckInitialization();
    bool AreAllManagersInitialized();

private:
	UPROPERTY()
	TMap<FName, TSoftClassPtr<AGameModeBase>> LevelGameModes;

    UPROPERTY()
    ANDStageManager* StageManager;

    UPROPERTY()
    ANDSpawnManager* SpawnManager;

    UPROPERTY()
    ANDUIManager* UIManager;

    UPROPERTY()
    ANDObjectPoolManager* ObjectManager;

    UPROPERTY()
    ANDEffectManager* EffectManager;

    UPROPERTY()
    ANDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    UNDDataManager* DataManager;

    UPROPERTY()
    UNDEventManager* EventManager;

    UPROPERTY()
    UNDScoreManager* ScoreManager;

    UPROPERTY()
    UNDSoundManager* SoundManager;

    UPROPERTY()
    ANDItemManager* ItemManager;

    EGameState              CurrentGameState;


    FTimerHandle InitializationTimerHandle;

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float InitializationCheckInterval = 0.5f; // 초기화 상태 확인 간격 (초)

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float MaxInitializationTime = 10.0f; // 최대 초기화 대기 시간 (초)

    float InitializationTimer = 0.0f;
};
