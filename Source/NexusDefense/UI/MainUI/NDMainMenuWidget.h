// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDMainMenuWidget.generated.h"

class ANDUIManager;
class UNDGameInstance;

UCLASS()
class NEXUSDEFENSE_API UNDMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MainUI")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "MainUI")
	void ExitGame();

	UFUNCTION(BlueprintCallable, Category = "MainUI")
	void OpenSettings();

	UFUNCTION(BlueprintCallable, Category = "MainUI")
	void ShowCredits();

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	UFUNCTION()
	void OnSettingsButtonClicked();


private:
	void CleanupAndOpenLevel(const FName& LevelName);


protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* SettingsMenu;

	UPROPERTY()
	ANDUIManager* UIManager;

	UPROPERTY()
	UNDGameInstance* GameInstance;
};
