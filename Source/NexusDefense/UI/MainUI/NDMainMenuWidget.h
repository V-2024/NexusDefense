// NDMainMenuWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDMainMenuWidget.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// 버튼 바인딩
	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	// 버튼 클릭 이벤트
private:
	UFUNCTION()
	void OnStartGameClicked();

	UFUNCTION()
	void OnExitGameClicked();
};