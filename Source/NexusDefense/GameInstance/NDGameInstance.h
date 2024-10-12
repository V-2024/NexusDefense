// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Types/NDGameTypes.h"
#include "NDGameInstance.generated.h"

class UNDStageManager;
class UNDSpawnManager;
class UNDUIManager;
class UNDObjectPoolManager;
class UNDEffectManager;
class UNDObjectPoolManager;
class UNDDataManager;
class UNDEventManager;
class UNDScoreManager;
class UNDSoundManager;
class UNDItemManager;
class ANDEnemyBase;
struct FPlanetInfo;

UCLASS()
class NEXUSDEFENSE_API UNDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UNDGameInstance();
	virtual void Init() override;
    virtual void OnStart() override;
    virtual void Shutdown() override;

    // Other Manager Access Functions
    FORCEINLINE UNDStageManager*        GetStageManager()       const { return StageManager; }
    FORCEINLINE UNDSpawnManager*        GetSpawnManager()       const { return SpawnManager; }
    FORCEINLINE UNDUIManager*           GetUIManager()          const { return UIManager; }
    FORCEINLINE UNDObjectPoolManager*   GetObjectManager()      const { return ObjectManager; }
    FORCEINLINE UNDEffectManager*       GetEffectManager()      const { return EffectManager; }
    FORCEINLINE UNDObjectPoolManager*   GetObjectPoolManager()  const { return ObjectManager; }
    FORCEINLINE UNDDataManager*         GetDataManager()        const { return DataManager; }
    FORCEINLINE UNDEventManager*        GetEventManager()       const { return EventManager; }
    FORCEINLINE UNDScoreManager*        GetScoreManager()       const { return ScoreManager; }
    FORCEINLINE UNDSoundManager*        GetSoundManager()       const { return SoundManager; }
    FORCEINLINE UNDItemManager*         GetItemManager()        const { return ItemManager; }
    FORCEINLINE EGameState              GetGameState()          const { return CurrentGameState; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    void ChangeGameModeForLevel(const FName& LevelName);
   
    void SetGameState(EGameState NewState);
    void SubscribeToEvents();
    void UnsubscribeFromEvents();
    void InitializeManagers();
    void CleanupManagers();

	AActor* EnemySpawned(TSubclassOf<AActor> Enemy);

    // event handeling level changed
    void OnLevelChanged(const FName& LevelName);

    void TriggerGameStartedEvent();
    void TriggerSelectStageEvent();
    TArray<FPlanetInfo> TriggerGetPlanetInfosEvent() const;
    void TriggerPlanetClickedEvent(int32 PlanetIndex);
    void TriggerEnemySpawn(ANDEnemyBase* Enemy) const;

private:
    template<typename T>
    void CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass, FName ManagerName);

    void SetLevelGameModes();
    void StartGame();
    void CheckInitialization();
    bool AreAllManagersInitialized();

private:
	UPROPERTY()
	TMap<FName, TSoftClassPtr<AGameModeBase>> LevelGameModes;

    UPROPERTY()
    UNDStageManager*        StageManager;
    UPROPERTY()
    UNDSpawnManager*        SpawnManager;
    UPROPERTY()
    UNDUIManager*           UIManager;
    UPROPERTY()
    UNDObjectPoolManager*   ObjectManager;
    UPROPERTY()
    UNDEffectManager*       EffectManager;
    UPROPERTY()
    UNDObjectPoolManager*   ObjectPoolManager;
    UPROPERTY()
    UNDDataManager*         DataManager;
    UPROPERTY()
    UNDEventManager*        EventManager;
    UPROPERTY()
    UNDScoreManager*        ScoreManager;
    UPROPERTY()
    UNDSoundManager*        SoundManager;
    UPROPERTY()
    UNDItemManager*         ItemManager;

    EGameState              CurrentGameState;

    FTimerHandle InitializationTimerHandle;

    FName CurrentLevelName;

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float InitializationCheckInterval = 0.5f; // 초기화 상태 확인 간격 (초)

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float MaxInitializationTime = 10.0f; // 최대 초기화 대기 시간 (초)

    float InitializationTimer = 0.0f;
};

template<typename T>
inline void UNDGameInstance::CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass, FName ManagerName)
{
    if (!ManagerPtr)
	{
		ManagerPtr = NewObject<T>(this, ManagerClass, ManagerName);
		//ManagerPtr->Initialize();
	}
}
