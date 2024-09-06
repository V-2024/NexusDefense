// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDInStageGameMode.h"
#include "Enemy/NDEnemyBase.h"

ANDInStageGameMode::ANDInStageGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/NexusDefense/Blueprint/BP_NDCharacterPlayerMelee.BP_NDCharacterPlayerMelee_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/NexusDefense.NDPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	PrimaryActorTick.bCanEverTick = false;
}

void ANDInStageGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ANDInStageGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	//GameManager->EndPlay(EndPlayReason);

	Super::EndPlay(EndPlayReason);
}

void ANDInStageGameMode::EndGame()
{
	
}

void ANDInStageGameMode::PauseGame()
{
	
}

void ANDInStageGameMode::ResumeGame()
{
	
}

void ANDInStageGameMode::AddScore(int32 Score)
{
	CurrentScore += Score;
}


//void ANDInStageGameMode::AddScore(int32 Score)
//{
//	CurrentScore += Score;
//}
//
//void ANDInStageGameMode::OnEnemyDefeated(ANDEnemyBase* DefeatedEnemy)
//{
//	AddScore(DefeatedEnemy->GetScore());
//}
//
//void ANDInStageGameMode::OnStageCompleted(int32 StageNumber)
//{
//	GameManager->OnStageCompleted(StageNumber);
//}
//
//void ANDInStageGameMode::OnGameOver()
//{
//	GameManager->OnGameOver();
//}
