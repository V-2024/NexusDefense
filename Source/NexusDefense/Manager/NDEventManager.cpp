// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDEventManager.h"
#include "Enemy/NDEnemyBase.h"
#include "Stages/FPlanetInfo.h"


void UNDEventManager::SubscribeToEvents()
{

}

void UNDEventManager::UnsubscribeFromEvents()
{

}

void UNDEventManager::TriggerStartLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerStartLevel"));

	if (OnStartLevel.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnStartLevel is bound"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnStartLevel is not bound"));
	}

	OnStartLevel.Broadcast();
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

void UNDEventManager::TriggerPlanetZoomIn(const FPlanetInfo& PlanetInfo)
{
}

void UNDEventManager::TriggerPlanetZoomOut()
{
}

void UNDEventManager::TriggerPlanetInfoUpdated(const FPlanetInfo& PlanetInfo)
{
}

void UNDEventManager::TriggerStageInfoUpdated(const FStageInfo& StageInfo)
{
}

void UNDEventManager::TriggerStageUnlocked(int32 StageID)
{
}




TArray<FPlanetInfo> UNDEventManager::TriggerGetPlanetInfos()
{
	if (OnGetPlanetInfos.IsBound())
	{
		return OnGetPlanetInfos.Execute();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnGetPlanetInfos is not bound"));
		return TArray<FPlanetInfo>();
	}
}

void UNDEventManager::TriggerStageSelectedMenu(EGameState GameState)
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerStageSelected"));

	if(OnStageSelected.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnStageSelected is bound"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnStageSelected is not bound"));
	}

	OnStageSelected.Broadcast(GameState);
}



void UNDEventManager::TriggerStageStarted(int32 StageNumber)
{
	OnStageStarted.Broadcast(StageNumber);
}

void UNDEventManager::TriggerStageCompleted(int32 StageID)
{
	OnStageCompleted.Broadcast(StageID);
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

void UNDEventManager::TriggerEnemyDamageTaken(ACharacter* HealthChangedCharacter, float Amount)
{
	OnHealthChanged.Broadcast(HealthChangedCharacter, Amount);
}

void UNDEventManager::TriggerEnemyDamageReceived(ACharacter* DamageTakenCharacter, FND_S_DamageInfo DamageInfo)
{
	OnDamageReceived.Broadcast(DamageTakenCharacter, DamageInfo);
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

