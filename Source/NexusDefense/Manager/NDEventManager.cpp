// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDEventManager.h"
#include "Enemy/NDEnemyBase.h"
#include "Item/NDItemBase.h"
#include "Character/NDCharacterBase.h"


void UNDEventManager::SubscribeToEvents()
{

}

void UNDEventManager::UnsubscribeFromEvents()
{

}

void UNDEventManager::TriggerGameLevelChanged(const FName& NewLevel)
{
	OnGameLevelChanged.Broadcast(NewLevel);
}

void UNDEventManager::TriggerGameStarted()
{
	OnGameStarted.Broadcast();
}

void UNDEventManager::TriggerGamePaused()
{
    OnGamePaused.Broadcast();
}

void UNDEventManager::TriggerGameResumed()
{
	OnGameResumed.Broadcast();
}

void UNDEventManager::TriggerGameOver()
{
	OnGameOver.Broadcast();
}

void UNDEventManager::TriggerStageSelected(EGameState GameState)
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerStageSelected"));

	OnStageSelected.Broadcast(GameState);
}

void UNDEventManager::TriggerStageStarted(int32 StageNumber)
{
	OnStageStarted.Broadcast(StageNumber);
}

void UNDEventManager::TriggerStageCompleted(int32 StageNumber)
{
	OnStageCompleted.Broadcast(StageNumber);
}

void UNDEventManager::TriggerWaveStarted(int32 StageNumber, int32 WaveNumber)
{
	OnWaveStarted.Broadcast(StageNumber, WaveNumber);
}

void UNDEventManager::TriggerWaveCompleted(int32 StageNumber, int32 WaveNumber)
{
	OnWaveCompleted.Broadcast(StageNumber, WaveNumber);
}

void UNDEventManager::TriggerEnemySpawned(ANDEnemyBase* Enemy)
{
	OnEnemySpawned.Broadcast(Enemy);
}

void UNDEventManager::TriggerBossSpawned(ANDEnemyBase* Boss)
{
	OnBossSpawned.Broadcast(Boss);
}

void UNDEventManager::TriggerEnemyDefeated(AActor* Enemy)
{
	OnEnemyDefeated.Broadcast(Enemy);
}

void UNDEventManager::TriggerBossDefeated(AActor* Boss)
{
	OnBossDefeated.Broadcast(Boss);
}

void UNDEventManager::TriggerScoreUpdated(int32 NewScore)
{
	OnScoreUpdated.Broadcast(NewScore);
}

void UNDEventManager::TriggerHighScoreAchieved(int32 NewHighScore)
{
	OnHighScoreAchieved.Broadcast(NewHighScore);
}

void UNDEventManager::TriggerObjectPoolCreated(FString PoolName, int32 PoolSize)
{
	OnObjectPoolCreated.Broadcast(PoolName, PoolSize);
}

void UNDEventManager::TriggerObjectPoolDepleted(FString PoolName)
{
	OnObjectPoolDepleted.Broadcast(PoolName);
}

void UNDEventManager::TriggerEffectStarted(FString EffectName, AActor* TargetActor)
{
	OnEffectStarted.Broadcast(EffectName, TargetActor);
}

void UNDEventManager::TriggerEffectEnded(FString EffectName, AActor* TargetActor)
{
	OnEffectEnded.Broadcast(EffectName, TargetActor);
}

void UNDEventManager::TriggerItemSpawned(ANDItemBase* SpawnedItem)
{
	OnItemSpawned.Broadcast(SpawnedItem);
}

void UNDEventManager::TriggerItemCollected(ANDItemBase* CollectedItem, ANDCharacterBase* Collector)
{
	OnItemCollected.Broadcast(CollectedItem, Collector);
}

void UNDEventManager::TriggerItemEffectApplied(ANDItemBase* UsedItem, ANDCharacterBase* User)
{
	OnItemEffectApplied.Broadcast(UsedItem, User);
}

void UNDEventManager::TriggerPlayerSpawned(ANDCharacterBase* SpawnedPlayer)
{
	OnPlayerSpawned.Broadcast(SpawnedPlayer);
}

void UNDEventManager::TriggerPlayerLevelUp(ANDCharacterBase* Player, int32 NewLevel)
{
	OnPlayerLevelUp.Broadcast(Player, NewLevel);
}

void UNDEventManager::TriggerPlayerDied(ANDCharacterBase* Player)
{
	OnPlayerDied.Broadcast(Player);
}

void UNDEventManager::TriggerUIInitialized()
{
	OnUIInitialized.Broadcast();
}

void UNDEventManager::TriggerUIButtonClicked(FName ButtonName)
{
	OnUIButtonClicked.Broadcast(ButtonName);
}

