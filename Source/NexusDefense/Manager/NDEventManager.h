// NDEventManager.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Types/NDGametypes.h"
#include "NDEventManager.generated.h"

// 스테이지 번호 추가 등의 추가정보 파라미터 추가)
// 실제 이벤트를 발생시키는 메서드 필요 (TriggerStageStart, TriggerStageEnd 등)

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

// Stage Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageSelected, EGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStarted, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageCompleted, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageEnd, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveStarted, int32, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWaveCompleted, int32, int32);


// Spawn Enemy Events Delegates
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, ANDEnemyBase*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBossSpawned, ANDEnemyBase*);


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


    // Stage Events
    FOnStageSelected        OnStageSelected;
    FOnStageStarted         OnStageStarted;
    FOnStageCompleted       OnStageCompleted;
    FOnStageEnd             OnStageEnd;
    FOnWaveStarted          OnWaveStarted;
    FOnWaveCompleted        OnWaveCompleted;


    // Spawn Enemy Events
    FOnEnemySpawned         OnEnemySpawned;
    FOnBossSpawned          OnBossSpawned;


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

    void TriggerStageSelected(EGameState GameState);

    void TriggerStageStarted(int32 StageNumber);

    void TriggerStageCompleted(int32 StageNumber);

    void TriggerWaveStarted(int32 StageNumber, int32 WaveNumber);

    void TriggerWaveCompleted(int32 StageNumber, int32 WaveNumber);

    void TriggerEnemySpawned(ANDEnemyBase* SpawnedEnemy);

    void TriggerBossSpawned(ANDEnemyBase* SpawnedBoss);

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
