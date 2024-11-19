// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDUIManager.h"
#include "UI/MainUI/NDPlanetOverviewWidget.h"
#include "UI/MainUI/NDPlanetDetailWidget.h"
#include "UI/MainUI/NDStageInfoWidget.h"
#include "UI/MainUI/NDMainMenuWidget.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"

UNDUIManager::UNDUIManager()
{
	static ConstructorHelpers::FClassFinder<UNDPlanetOverviewWidget> PlanetOverviewWidgetClassFinder(TEXT("/Game/NexusDefense/UI/MainUI/WBP_PlanetOverviewWidget.WBP_PlanetOverviewWidget_C"));
	static ConstructorHelpers::FClassFinder<UNDPlanetDetailWidget> PlanetDetailWidgetClassFinder(TEXT("/Game/NexusDefense/UI/MainUI/WBP_PlanetDetailWidget.WBP_PlanetDetailWidget_C"));
	static ConstructorHelpers::FClassFinder<UNDStageInfoWidget> StageInfoWidgetClassFinder(TEXT("/Game/NexusDefense/UI/MainUI/WBP_StageInfoWidget.WBP_StageInfoWidget_C"));
	static ConstructorHelpers::FClassFinder<UNDMainMenuWidget> MainMenuWidgetClassFinder(TEXT("/Game/NexusDefense/UI/MainUI/WBP_MainMenuWidget.WBP_MainMenuWidget_C"));

	
	if (PlanetOverviewWidgetClassFinder.Succeeded())
		PlanetOverviewWidgetClass = PlanetOverviewWidgetClassFinder.Class;
	if (PlanetDetailWidgetClassFinder.Succeeded())
		PlanetDetailWidgetClass = PlanetDetailWidgetClassFinder.Class;
	if (StageInfoWidgetClassFinder.Succeeded())
		StageInfoWidgetClass = StageInfoWidgetClassFinder.Class;
	if (MainMenuWidgetClassFinder.Succeeded())
		MainMenuWidgetClass = MainMenuWidgetClassFinder.Class;


	MainMenuWidget = nullptr;

	bIsInPlanetView = false;
}

void UNDUIManager::StartUI()
{
	UpdateUI(EGameState::Ready);
}

void UNDUIManager::UpdateUI(EGameState NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateUI"));
	
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
	// 다른 UI들 닫기
	CloseGameUI();
	ClosePauseMenu();
	CloseGameOverUI();
	CloseStageSelectUI();

	// 메인 메뉴 생성 및 표시
	if (!MainMenuWidget && MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UNDMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	}

	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}

	// 입력 모드 설정
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
}

void UNDUIManager::ShowStageSelectUI()
{
	// 기존 UI 제거
	CloseMainMenu();
	CloseGameUI();
	ClosePauseMenu();
	CloseGameOverUI();

	UE_LOG(LogTemp, Warning, TEXT("StageSelectedLevel"));
	// 행성 오버뷰 표시
	ShowPlanetOverview();

	// 입력 모드 설정
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
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

void UNDUIManager::ShowPlanetOverview()
{
	if (!PlanetOverviewWidget && PlanetOverviewWidgetClass)
	{
		PlanetOverviewWidget = CreateWidget<UNDPlanetOverviewWidget>(GetWorld(), PlanetOverviewWidgetClass);
	}

	if (PlanetOverviewWidget)
	{
		PlanetOverviewWidget->AddToViewport();
        
		// 행성 상세 정보 위젯이 있다면 제거
		if (PlanetDetailWidget)
		{
			PlanetDetailWidget->RemoveFromParent();
			PlanetDetailWidget = nullptr;
		}
	}
}

void UNDUIManager::ShowPlanetDetail(const FPlanetInfo& PlanetInfo)
{
	if (!PlanetDetailWidget && PlanetDetailWidgetClass)
	{
		PlanetDetailWidget = CreateWidget<UNDPlanetDetailWidget>(GetWorld(), PlanetDetailWidgetClass);
	}

	if (PlanetDetailWidget)
	{
		CurrentPlanetInfo = PlanetInfo;
		PlanetDetailWidget->UpdatePlanetInfo(PlanetInfo);
		PlanetDetailWidget->AddToViewport();
		bIsInPlanetView = true;

		// 스테이지 정보 업데이트
		if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetWorld()->GetGameInstance()))
		{
			for (int32 StageID : PlanetInfo.StageIDs)
			{
				FStageInfo StageInfo = GameInstance->GetStageInfo(StageID);
				UpdateStageInfo(StageInfo);
			}
		}
	}
}

void UNDUIManager::UpdateStageInfo(const FStageInfo& StageInfo)
{
	if (!StageInfoWidget && StageInfoWidgetClass)
	{
		StageInfoWidget = CreateWidget<UNDStageInfoWidget>(GetWorld(), StageInfoWidgetClass);
	}

	if (StageInfoWidget)
	{
		CurrentStageInfo = StageInfo;
		StageInfoWidget->SetStageInfo(StageInfo);
        
		if (!StageInfoWidget->IsInViewport())
		{
			StageInfoWidget->AddToViewport();
		}
	}
}

void UNDUIManager::HandlePlanetZoomIn(const FPlanetInfo& PlanetInfo)
{
	if (!bIsInPlanetView)
	{
		ShowPlanetDetail(PlanetInfo);
        
		if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetWorld()->GetGameInstance()))
		{
			if (UNDEventManager* EventManager = GameInstance->GetEventManager())
			{
				EventManager->TriggerPlanetZoomIn(PlanetInfo);
			}
		}
	}
}

void UNDUIManager::HandlePlanetZoomOut()
{
	if (bIsInPlanetView)
	{
		bIsInPlanetView = false;
        
		if (PlanetDetailWidget)
		{
			PlanetDetailWidget->RemoveFromParent();
			PlanetDetailWidget = nullptr;
		}

		if (StageInfoWidget)
		{
			StageInfoWidget->RemoveFromParent();
			StageInfoWidget = nullptr;
		}

		ShowPlanetOverview();
        
		if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetWorld()->GetGameInstance()))
		{
			if (UNDEventManager* EventManager = GameInstance->GetEventManager())
			{
				EventManager->TriggerPlanetZoomOut();
			}
		}
	}
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

