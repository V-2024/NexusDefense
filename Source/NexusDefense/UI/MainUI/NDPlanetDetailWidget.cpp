// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDPlanetDetailWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "NDStageButtonWidget.h"

void UNDPlanetDetailWidget::SetPlanetInfo(const FPlanetInfo& InPlanetInfo)
{
	PlanetInfo = InPlanetInfo;

	if (PlanetDetailImage)
	{
		PlanetDetailImage->SetBrushFromTexture(PlanetInfo.PlanetImage);
	}

	if (PlanetNameText)
	{
		PlanetNameText->SetText(FText::FromName(PlanetInfo.PlanetName));
	}

	if (PlanetDescriptionText)
	{
		PlanetDescriptionText->SetText(FText::FromString(PlanetInfo.Description));
	}

	UpdateStageButtons();
}


void UNDPlanetDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNDPlanetDetailWidget::UpdateStageButtons()
{
	if (!StageButtonContainer || !StageButtonWidgetClass) return;

	StageButtonContainer->ClearChildren();

	for (int32 StageID : PlanetInfo.StageIDs)
	{
		UNDStageButtonWidget* StageButton = CreateWidget<UNDStageButtonWidget>(this, StageButtonWidgetClass);
		if (StageButton)
		{
			StageButton->SetStageID(StageID);
			// StageButton->SetStageInfo(...); // 스테이지 정보 설정
			StageButtonContainer->AddChild(StageButton);
		}
	}
}
