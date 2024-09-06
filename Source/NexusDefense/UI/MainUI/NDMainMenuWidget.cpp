// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/NDUIManager.h"
#include "Manager/NDEventManager.h"

void UNDMainMenuWidget::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));

    if (UIManager)
    {
        UIManager->CloseMainMenu();
    }

    // 레벨 전환
    // Game Start Event
    UNDEventManager::GetInstance()->TriggerGameLevelChanged("EnemyTestLevel");
}

void UNDMainMenuWidget::ExitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("ExitGame"));
}

void UNDMainMenuWidget::OpenSettings()
{

}

void UNDMainMenuWidget::ShowCredits()
{
}

void UNDMainMenuWidget::OnStartButtonClicked()
{
}

void UNDMainMenuWidget::OnExitButtonClicked()
{
}

void UNDMainMenuWidget::OnSettingsButtonClicked()
{
}

void UNDMainMenuWidget::CleanupAndOpenLevel(const FName& LevelName)
{
    // 게임 모드를 통해 추가적인 클린업 수행
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
    if (GameMode)
    {
        GameMode->ResetLevel();
    }

    // 자신을 뷰포트에서 제거
    RemoveFromParent();

    // 새 레벨 열기
    UGameplayStatics::OpenLevel(this, LevelName);
}

void UNDMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// UIManager 초기화
	if (UIManager)
	{
		UIManager = ANDUIManager::GetInstance();
	}
}
