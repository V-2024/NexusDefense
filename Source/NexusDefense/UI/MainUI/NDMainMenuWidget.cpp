// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/NDEventManager.h"
#include "GameInstance/NDGameInstance.h"

void UNDMainMenuWidget::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));

    // ���� ��ȯ
    GameInstance->ChangeGameModeForLevel("StageSelectLevel");

    if (GameInstance)
    {
        GameInstance->TriggerGameStartedEvent();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance is nullptr"));
    }
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
    // ���� ��带 ���� �߰����� Ŭ���� ����
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
    if (GameMode)
    {
        GameMode->ResetLevel();
    }

    // �ڽ��� ����Ʈ���� ����
    RemoveFromParent();

    // �� ���� ����
    UGameplayStatics::OpenLevel(this, LevelName);
}

void UNDMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

    // get game instance
    GameInstance = Cast<UNDGameInstance>(GetWorld()->GetGameInstance());
}
