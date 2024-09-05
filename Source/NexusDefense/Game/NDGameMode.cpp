// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDGameMode.h"
#include "Manager/NDGameManager.h"
#include "Enemy/NDEnemyBase.h"

ANDGameMode::ANDGameMode()
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
	CurrentScore = 0;
}

void ANDGameMode::BeginPlay()
{
	Super::BeginPlay();

	// spawn actor for the game manager
	GameManager = GetWorld()->SpawnActor<ANDGameManager>(ANDGameManager::StaticClass());

	InitializeManagers();

	GameManager->StartGame();
}

void ANDGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnsubscribeFromEvents();

	GameManager->EndPlay(EndPlayReason);

	Super::EndPlay(EndPlayReason);
}

void ANDGameMode::InitializeManagers()
{
	GameManager->InitializeManagers(GetWorld());

	//FTimerHandle InitTimer;
	//GetWorldTimerManager().SetTimer(InitTimer, [this]() {
	//	if (GetWorld())
	//	{
	//		//GameManager->InitializeManagers(GetWorld());
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("GameManagerClass is not set!"));
	//	}
	//}, 0.1f, false);
}

void ANDGameMode::SubscribeToEvents()
{
	if (GameManager)
	{
		GameManager->SubscribeToEvents();
	}
}

void ANDGameMode::UnsubscribeFromEvents()
{
	if (GameManager)
	{
		GameManager->UnsubscribeFromEvents();
	}
}

void ANDGameMode::StartGame()
{
	CurrentScore = 0;

	if (GameManager)
	{
		GameManager->StartGame();
	}

	// Add Start Game Logic
}

void ANDGameMode::EndGame()
{
	if (GameManager)
	{
		GameManager->EndGame();
	}

	// Add End Game Logic
}

void ANDGameMode::PauseGame()
{
	if (GameManager)
	{
		GameManager->PauseGame();
	}
}

void ANDGameMode::ResumeGame()
{
	if (GameManager)
	{
		GameManager->ResumeGame();
	}
}

void ANDGameMode::AddScore(int32 Score)
{
	CurrentScore += Score;

	// Add Score Logic
}

void ANDGameMode::OnEnemyDefeated(ANDEnemyBase* DefeatedEnemy)
{
	//AddScore(DefeatedEnemy->GetScoreValue());
}

void ANDGameMode::OnStageCompleted(int32 StageNumber)
{
	// Add Stage Complete Logic
	//AddScore(StageNumber * 100);
}

void ANDGameMode::OnGameOver()
{
	EndGame();

	// Add Game Over Logic
}
