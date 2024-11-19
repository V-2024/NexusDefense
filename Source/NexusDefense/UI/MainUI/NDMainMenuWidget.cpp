// NDMainMenuWidget.cpp
#include "UI/MainUI/NDMainMenuWidget.h"
#include "Components/Button.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UNDMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ?? ?? ??? ???
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UNDMainMenuWidget::OnStartGameClicked);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UNDMainMenuWidget::OnExitGameClicked);
	}
}

void UNDMainMenuWidget::OnStartGameClicked()
{
	if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
	{
		// ???? ?? ???? ??
		GameInstance->TriggerSelectStageEvent();
	}
}

void UNDMainMenuWidget::OnExitGameClicked()
{
	// ?? ??
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}