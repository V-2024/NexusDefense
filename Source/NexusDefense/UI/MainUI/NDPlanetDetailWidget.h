// NDPlanetDetailWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/NDGameTypes.h"
#include "Stages/FPlanetInfo.h"
#include "NDPlanetDetailWidget.generated.h"

class UImage;
class UTextBlock;
class UScrollBox;
class UButton;
class UNDStageInfoWidget;

UCLASS()
class NEXUSDEFENSE_API UNDPlanetDetailWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* PlanetImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlanetNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* StageScrollBox;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UNDStageInfoWidget> StageInfoWidgetClass;

public:
	void UpdatePlanetInfo(const FPlanetInfo& PlanetInfo);
	void UpdateStageList(const TArray<int32>& StageIDs);

private:
	UPROPERTY()
	TArray<UNDStageInfoWidget*> StageWidgets;

	UPROPERTY()
	FPlanetInfo CurrentPlanetInfo;

	UFUNCTION()
	void OnBackButtonClicked();

	void ClearStageList();
	void CreateStageWidgets(const TArray<int32>& StageIDs);
};