// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDUIManager.h"

UNDUIManager::UNDUIManager()
{
	
	//static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassFinder(TEXT("/Game/NexusDefense/Blueprint/UI/MainUI/WBP_MainmenuWidget.WBP_MainmenuWidget_C"));
	//static ConstructorHelpers::FClassFinder<UUserWidget> StageSelectWidgetClassFinder(TEXT("/Game/NexusDefense/Blueprint/UI/MainUI/WBP_StageSelectWidget.WBP_StageSelectWidget_C"));
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
	
}

void UNDUIManager::ShowStageSelectUI()
{


	UE_LOG(LogTemp, Warning, TEXT("ShowStageSelectUI"));



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

}

void UNDUIManager::ClosePauseMenu()
{

}

void UNDUIManager::CloseGameUI()
{

}

void UNDUIManager::CloseGameOverUI()
{

}

void UNDUIManager::CloseStageSelectUI()
{

}

void UNDUIManager::OnPlanetClicked(int32 PlanetIndex)
{
	//StageSelectWidget->OnPlanetClicked(PlanetIndex);
}

