// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDUIManager.h"
#include "Manager/NDGameManager.h"
#include "UI/MainUI/NDMainMenuWidget.h"
#include "UI/MainUI/NDGameUIWidget.h"
#include "UI/MainUI/NDPauseMenuWidget.h"
#include "UI/MainUI/NDGameOverUIWidget.h"
#include "UI/MainUI/NDStageSelectWidget.h"

ANDUIManager* ANDUIManager::Instance = nullptr;

ANDUIManager::ANDUIManager()
{
	PrimaryActorTick.bCanEverTick = true;

	MainMenuWidgetClass = nullptr;
	GameUIWidgetClass = nullptr;
	PauseMenuWidgetClass = nullptr;
	GameOverUIWidgetClass = nullptr;
	StageSelectUIWidgetClass = nullptr;

	MainMenuWidget = nullptr;
	GameUIWidget = nullptr;
	PauseMenuWidget = nullptr;
	GameOverUIWidget = nullptr;
	StageSelectWidget = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassFinder(TEXT("/Game/NexusDefense/UI/MainUI/WBP_MainmenuWidget.WBP_MainmenuWidget_C"));

	if (MainMenuWidgetClassFinder.Class)
	{
		MainMenuWidgetClass = MainMenuWidgetClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenuWidgetClass is not found!"));
	}

	// Find Other Widget Classes..
}

void ANDUIManager::UpdateUI(EGameState NewState)
{
	switch (NewState)
	{
		case EGameState::Ready:
			ShowMainMenu();
			break;
		case EGameState::Playing:
			ShowGameUI();
			break;
		case EGameState::Paused:
			ShowPauseMenu();
			break;
		case EGameState::GameOver:
			ShowGameOverUI();
			break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void ANDUIManager::BeginPlay()
{
	Super::BeginPlay();

	if (!Instance)
	{
		Instance = this;
	}
	else
	{
		Destroy();
	}
	
	CreateWidgets();
}

// Called every frame
void ANDUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDUIManager::CreateWidgets()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UNDMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

	}
	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UNDPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
		//PauseMenuWidget->AddToViewport();
	}
	if (GameUIWidgetClass)
	{
		GameUIWidget = CreateWidget<UNDGameUIWidget>(GetWorld(), GameUIWidgetClass);
		//GameUIWidget->AddToViewport();
	}
	if (GameOverUIWidgetClass)
	{
		GameOverUIWidget = CreateWidget<UNDGameOverUIWidget>(GetWorld(), GameOverUIWidgetClass);
		//GameOverUIWidget->AddToViewport();
	}
	if (StageSelectUIWidgetClass)
	{
		StageSelectWidget = CreateWidget<UNDStageSelectWidget>(GetWorld(), StageSelectUIWidgetClass);
		//StageSelectUIWidget->AddToViewport();
	}
}

void ANDUIManager::ShowMainMenu()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget->AddToViewport();

		// ��ü ȭ�� ��� ����
		MainMenuWidget->SetDesiredSizeInViewport(FVector2D(1920, 1080));  // ���ϴ� �ػ�
		MainMenuWidget->SetAnchorsInViewport(FAnchors(0, 0, 1, 1));
		MainMenuWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));

		// �Է� ��� ����
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(true);
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputMode);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenuWidgetClass is not set!"));
	}
}

void ANDUIManager::ShowPauseMenu()
{

}

void ANDUIManager::ShowGameUI()
{

}

void ANDUIManager::ShowGameOverUI()
{

}

void ANDUIManager::ShowStageSelectUI()
{

}

void ANDUIManager::CloseMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
	}
}

void ANDUIManager::ClosePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
	}
}

void ANDUIManager::CloseGameUI()
{
	if (GameUIWidget)
	{
		GameUIWidget->RemoveFromParent();
	}
}

void ANDUIManager::CloseGameOverUI()
{
	if (GameOverUIWidget)
	{
		GameOverUIWidget->RemoveFromParent();
	}
}

void ANDUIManager::CloseStageSelectUI()
{
	if (StageSelectWidget)
	{
		StageSelectWidget->RemoveFromParent();
	}
}
