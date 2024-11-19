// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Stages/FStageInfo.h"
#include "Types/NDGameTypes.h"
#include "Stages/FPlanetInfo.h"
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
    FORCEINLINE EGameState              GetGameState()          const { return CurrentGameState; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    void ChangeGameModeForLevel(const FName& LevelName);
   
    void SetGameState(EGameState NewState);
    void SubscribeToEvents();
    void UnsubscribeFromEvents();
    void InitializeManagers();
    void CleanupManagers();

    // event handeling level changed
    void OnLevelChanged(const FName& LevelName);

    void TriggerGameStartedEvent();
    void TriggerSelectStageEvent();
    TArray<FPlanetInfo> TriggerGetPlanetInfosEvent() const;
    void TriggerPlanetClickedEvent(const FPlanetInfo& PlanetInfo);
    void TriggerEnemySpawn(ANDEnemyBase* Enemy) const;

	UFUNCTION(BlueprintCallable, Category = "Stage System")
	FStageInfo GetStageInfo(int32 StageID) const;
    
	UFUNCTION(BlueprintCallable, Category = "Stage System")
	FPlanetInfo GetPlanetInfo(const FName& PlanetName) const;
	
	UFUNCTION(BlueprintCallable, Category = "Planet System")
	TArray<FPlanetInfo> GetPlanets() const;

private:
    template<typename T>
    void CreateManager(T*& ManagerPtr, TSubclassOf<T> ManagerClass, FName ManagerName);

    void SetLevelGameModes();
    void StartGame();
    void CheckInitialization();
    bool AreAllManagersInitialized();

	void InitializeGameData();
	void LoadStageData();
	void LoadPlanetData();

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
	TMap<int32, FStageInfo> StageDataMap;
    
	UPROPERTY()
	TMap<FName, FPlanetInfo> PlanetDataMap;

    EGameState              CurrentGameState;

    FTimerHandle InitializationTimerHandle;

    FName CurrentLevelName;

	

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float InitializationCheckInterval = 0.5f; // �ʱ�ȭ ���� Ȯ�� ���� (��)

    UPROPERTY(EditDefaultsOnly, Category = "Initialization")
    float MaxInitializationTime = 10.0f; // �ִ� �ʱ�ȭ ��� �ð� (��)

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
