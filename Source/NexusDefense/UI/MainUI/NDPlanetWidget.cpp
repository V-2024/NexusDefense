// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDPlanetWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UNDPlanetWidget::SetPlanetInfo(const FPlanetInfo& InPlanetInfo)
{
	PlanetInfo = InPlanetInfo;

	if (PlanetImage)
	{
		PlanetImage->SetBrushFromTexture(PlanetInfo.PlanetImage);
	}

	if (PlanetNameText)
	{
		PlanetNameText->SetText(FText::FromName(PlanetInfo.PlanetName));
	}

	OnPlanetInfoUpdated();
}

void UNDPlanetWidget::SetPlanetIndex(int32 InPlanetIndex)
{
	PlanetIndex = InPlanetIndex;
}

void UNDPlanetWidget::SetUnlocked(bool bInUnlocked)
{
	PlanetInfo.bIsUnlocked = bInUnlocked;
	OnPlanetInfoUpdated();
}

void UNDPlanetWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
