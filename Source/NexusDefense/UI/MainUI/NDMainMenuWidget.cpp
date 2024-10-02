// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/NDEventManager.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"

void UNDMainMenuWidget::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));

    // 레벨 전환
    GameInstance->ChangeGameModeForLevel("StageSelectLevel");

    // GameInstance에서 변경해야할 필요 있음
    GameInstance->SetGameState(EGameState::StageSelect);


    GameInstance->GetEventManager()->TriggerStageSelected(GameInstance->GetGameState());
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

    // get game instance
    GameInstance = Cast<UNDGameInstance>(GetWorld()->GetGameInstance());
}
