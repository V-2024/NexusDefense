// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDUIManager.h"
#include "UI/MainUI/NDMainMenuWidget.h"
#include "UI/MainUI/NDGameUIWidget.h"
#include "UI/MainUI/NDPauseMenuWidget.h"
#include "UI/MainUI/NDGameOverUIWidget.h"
#include "UI/MainUI/NDStageSelectWidget.h"

UNDUIManager::UNDUIManager()
{
	MainMenuWidgetClass			= nullptr;
	GameUIWidgetClass			= nullptr;
	PauseMenuWidgetClass		= nullptr;
	GameOverUIWidgetClass		= nullptr;
	StageSelectUIWidgetClass	= nullptr;
	MainMenuWidget				= nullptr;
	GameUIWidget				= nullptr;
	PauseMenuWidget				= nullptr;
	GameOverUIWidget			= nullptr;
	StageSelectWidget			= nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassFinder(TEXT("/Game/NexusDefense/Blueprint/UI/MainUI/WBP_MainmenuWidget.WBP_MainmenuWidget_C"));
	static ConstructorHelpers::FClassFinder<UUserWidget> StageSelectWidgetClassFinder(TEXT("/Game/NexusDefense/Blueprint/UI/MainUI/WBP_StageSelectWidget.WBP_StageSelectWidget_C"));

	if (MainMenuWidgetClassFinder.Class && StageSelectWidgetClassFinder.Class)
	{
		MainMenuWidgetClass = MainMenuWidgetClassFinder.Class;
		StageSelectUIWidgetClass = StageSelectWidgetClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenuWidgetClass or StageSelectWidgetClass is not found!"));
	}
}

void UNDUIManager::StartUI()
{
	UpdateUI(EGameState::Ready);
}

void UNDUIManager::UpdateUI(EGameState NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateUI"));

	UE_LOG(LogTemp, Warning, TEXT("this UIManager address: %p"), this);
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
		case EGameState::StageSelect:
			ShowStageSelectUI();
			break;
		case EGameState::GameOver:
			ShowGameOverUI();
			break;
	default:
		break;
	}
}


void UNDUIManager::CreateWidgets()
{
	//if (PauseMenuWidgetClass)
	//{
	//	PauseMenuWidget = CreateWidget<UNDPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
	//	//PauseMenuWidget->AddToViewport();
	//}
	//if (GameUIWidgetClass)
	//{
	//	GameUIWidget = CreateWidget<UNDGameUIWidget>(GetWorld(), GameUIWidgetClass);
	//	//GameUIWidget->AddToViewport();
	//}
	//if (GameOverUIWidgetClass)
	//{
	//	GameOverUIWidget = CreateWidget<UNDGameOverUIWidget>(GetWorld(), GameOverUIWidgetClass);
	//	//GameOverUIWidget->AddToViewport();
	//}
}

void UNDUIManager::ShowMainMenu()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UNDMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

	}

	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();

		// 전체 화면 모드 설정
		//MainMenuWidget->SetDesiredSizeInViewport(FVector2D(1920, 1080));  // 원하는 해상도
		//MainMenuWidget->SetAnchorsInViewport(FAnchors(0, 0, 1, 1));
		//MainMenuWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));

		// 입력 모드 설정
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

void UNDUIManager::ShowStageSelectUI()
{

	if (StageSelectUIWidgetClass)
	{
		StageSelectWidget = CreateWidget<UNDStageSelectWidget>(GetWorld(), StageSelectUIWidgetClass);
	}

	UE_LOG(LogTemp, Warning, TEXT("ShowStageSelectUI"));

	if(StageSelectWidget)
	{
		StageSelectWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageSelectWidget is not set!"));
	}

	// 입력 모드 설정
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
}

void UNDUIManager::ShowPauseMenu()
{

}

void UNDUIManager::ShowGameUI()
{

}

void UNDUIManager::ShowGameOverUI()
{

}


void UNDUIManager::CloseMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
	}
}

void UNDUIManager::ClosePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
	}
}

void UNDUIManager::CloseGameUI()
{
	if (GameUIWidget)
	{
		GameUIWidget->RemoveFromParent();
	}
}

void UNDUIManager::CloseGameOverUI()
{
	if (GameOverUIWidget)
	{
		GameOverUIWidget->RemoveFromParent();
	}
}

void UNDUIManager::CloseStageSelectUI()
{
	if (StageSelectWidget)
	{
		StageSelectWidget->RemoveFromParent();
	}
}
