// NDEventManager.h
#pragma once

#include "CoreMinimal.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "Stages/FPlanetInfo.h"
#include "Stages/FStageInfo.h"
#include "UObject/NoExportTypes.h"
#include "Types/NDGametypes.h"
#include "NDEventManager.generated.h"



class ANDEnemyBase;
class ANDItemBase;
class ANDCharacterBase;

DECLARE_MULTICAST_DELEGATE(FOnStartLevel);

// Game Level Change Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameLevelChanged, const FName&);

// Game Events Delegates
DECLARE_MULTICAST_DELEGATE(FOnGameStarted);
DECLARE_MULTICAST_DELEGATE(FOnGamePaused);
DECLARE_MULTICAST_DELEGATE(FOnGameResumed);
DECLARE_MULTICAST_DELEGATE(FOnGameOver);

// Planet Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlanetClicked, int32);

// Planet Navigation Events
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlanetZoomIn, const FPlanetInfo&);
DECLARE_MULTICAST_DELEGATE(FOnPlanetZoomOut);

// Stage Events Delegates
DECLARE_DELEGATE_RetVal(TArray<FPlanetInfo>, FOnGetPlanetInfos);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageSelected, EGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStarted, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageCompleted, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageEnd, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveStarted, int32, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveCompleted, int32, int32);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlanetZoomIn, const FPlanetInfo&);
DECLARE_MULTICAST_DELEGATE(FOnPlanetZoomOut);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlanetInfoUpdated, const FPlanetInfo&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageInfoUpdated, const FStageInfo&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageUnlocked, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageCompleted, int32);

// Spawn Enemy Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, ANDEnemyBase*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBossSpawned, ANDEnemyBase*);

// Damage Events
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged1, ACharacter*, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDamageReceived, ACharacter*, FND_S_DamageInfo);

// Enemy Dead Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDefeated, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBossDefeated, AActor*);


// Score Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHighScoreAchieved, int32);


// ObjectPool Events Delegates
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectPoolCreated, FString, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectPoolDepleted, FString);


// Effect Events Delegates
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectStarted, FString, AActor*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectEnded, FString, AActor*);


// Item Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemSpawned, ANDItemBase*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemCollected, ANDItemBase*, ANDCharacterBase*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemEffectApplied, ANDItemBase*, ANDCharacterBase*);


// Player Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerSpawned, ANDCharacterBase*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerLevelUp, ANDCharacterBase*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDied, ANDCharacterBase*);


// UIManager Events Delegates
DECLARE_MULTICAST_DELEGATE(FOnUIInitialized);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUIButtonClicked, FName);



UCLASS()
class NEXUSDEFENSE_API UNDEventManager : public UObject
{
    GENERATED_BODY()

public:
    FOnStartLevel		    OnStartLevel;

    // Game Level Change Events
    FOnGameLevelChanged     OnGameLevelChanged;

    // Game Events
    FOnGameStarted          OnGameStarted;
    FOnGamePaused           OnGamePaused;
    FOnGameResumed          OnGameResumed;
    FOnGameOver             OnGameOver;

    // Planet Events
    FOnPlanetClicked        OnPlanetClicked;
    

    // Stage Events
    FOnGetPlanetInfos       OnGetPlanetInfos;
    FOnStageSelected        OnStageSelected;
    FOnStageStarted         OnStageStarted;
    FOnStageCompleted       OnStageCompleted;
    //FOnStageEnd             OnStageEnd;
    FOnWaveStarted          OnWaveStarted;
    FOnWaveCompleted        OnWaveCompleted;
    FOnPlanetZoomIn         OnPlanetZoomIn;
    FOnPlanetZoomOut        OnPlanetZoomOut;
    FOnPlanetInfoUpdated    OnPlanetInfoUpdated;
    FOnStageInfoUpdated     OnStageInfoUpdated;
    FOnStageUnlocked        OnStageUnlocked;

    
    // Spawn Enemy Events
    FOnEnemySpawned         OnEnemySpawned;
    FOnBossSpawned          OnBossSpawned;

    
    // Damage Events
    FOnHealthChanged1        OnHealthChanged;
    FOnDamageReceived       OnDamageReceived;

    
    // Enemy Dead Events
    FOnEnemyDefeated        OnEnemyDefeated;
    FOnBossDefeated         OnBossDefeated;


    // Score Events
    FOnScoreUpdated         OnScoreUpdated;
    FOnHighScoreAchieved    OnHighScoreAchieved;


    // ObjectPool Events
    FOnObjectPoolCreated    OnObjectPoolCreated;
    FOnObjectPoolDepleted   OnObjectPoolDepleted;


    // Effect Events
    FOnEffectStarted        OnEffectStarted;
    FOnEffectEnded          OnEffectEnded;


    // Item Events
    FOnItemSpawned          OnItemSpawned;
    FOnItemCollected        OnItemCollected;
    FOnItemEffectApplied    OnItemEffectApplied;


    // Player Events
    FOnPlayerSpawned        OnPlayerSpawned;
    FOnPlayerLevelUp        OnPlayerLevelUp;
    FOnPlayerDied           OnPlayerDied;


    // UI Events
    FOnUIInitialized        OnUIInitialized;
    FOnUIButtonClicked      OnUIButtonClicked;

public:
    void SubscribeToEvents();

    void UnsubscribeFromEvents();

    void TriggerStartLevel();

    // Event Trigger Methods
    void TriggerGameLevelChanged(const FName& NewLevel);

    void TriggerGameStarted();

    void TriggerGamePaused();

    void TriggerGameResumed();

    void TriggerGameOver();

    TArray<FPlanetInfo> TriggerGetPlanetInfos();

    // Stage Triggers
    void TriggerStageSelectedMenu(EGameState GameState);
    void TriggerStageStarted(int32 StageNumber);
    void TriggerStageCompleted(int32 StageID);
    void TriggerWaveStarted(int32 StageNumber, int32 WaveNumber);
    void TriggerWaveCompleted(int32 StageNumber, int32 WaveNumber);
    void TriggerPlanetZoomIn(const FPlanetInfo& PlanetInfo);
    void TriggerPlanetZoomOut();
    void TriggerPlanetInfoUpdated(const FPlanetInfo& PlanetInfo);
    void TriggerStageInfoUpdated(const FStageInfo& StageInfo);
    void TriggerStageUnlocked(int32 StageID);
    
    
    void TriggerEnemySpawned(ANDEnemyBase* SpawnedEnemy);

    void TriggerBossSpawned(ANDEnemyBase* SpawnedBoss);

    void TriggerEnemyDamageTaken(ACharacter* HealthChangedCharacter, float Amount);

    void TriggerEnemyDamageReceived(ACharacter* DamageTakenCharacter, FND_S_DamageInfo DamageInfo);

    void TriggerEnemyDefeated(AActor* DefeatedEnemy);

    void TriggerBossDefeated(AActor* DestroyedBoss);

    void TriggerScoreUpdated(int32 NewScore);

    void TriggerHighScoreAchieved(int32 NewHighScore);

    void TriggerObjectPoolCreated(FString PoolName, int32 PoolSize);

    void TriggerObjectPoolDepleted(FString PoolName);

    void TriggerEffectStarted(FString EffectName, AActor* TargetActor);

    void TriggerEffectEnded(FString EffectName, AActor* TargetActor);

    void TriggerItemSpawned(ANDItemBase* SpawnedItem);

    void TriggerItemCollected(ANDItemBase* CollectedItem, ANDCharacterBase* Collector);

    void TriggerItemEffectApplied(ANDItemBase* UsedItem, ANDCharacterBase* User);

    void TriggerPlayerSpawned(ANDCharacterBase* SpawnedPlayer);

    void TriggerPlayerLevelUp(ANDCharacterBase* Player, int32 NewLevel);

    void TriggerPlayerDied(ANDCharacterBase* Player);

    void TriggerUIInitialized();

    void TriggerUIButtonClicked(FName ButtonName);
};
