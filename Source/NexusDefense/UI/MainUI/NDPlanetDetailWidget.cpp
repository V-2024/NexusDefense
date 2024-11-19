// NDPlanetDetailWidget.cpp
#include "UI/MainUI/NDPlanetDetailWidget.h"
#include "UI/MainUI/NDStageInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"

void UNDPlanetDetailWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UNDPlanetDetailWidget::OnBackButtonClicked);
    }
}

void UNDPlanetDetailWidget::NativeDestruct()
{
    Super::NativeDestruct();

    if (BackButton)
    {
        BackButton->OnClicked.RemoveAll(this);
    }
}

void UNDPlanetDetailWidget::UpdatePlanetInfo(const FPlanetInfo& PlanetInfo)
{
    CurrentPlanetInfo = PlanetInfo;

    if (PlanetImage)
    {
        PlanetImage->SetBrushFromTexture(PlanetInfo.PlanetImage);
    }

    if (PlanetNameText)
    {
        PlanetNameText->SetText(FText::FromName(PlanetInfo.PlanetName));
    }

    if (DescriptionText)
    {
        DescriptionText->SetText(FText::FromString(PlanetInfo.Description));
    }

    UpdateStageList(PlanetInfo.StageIDs);
}

void UNDPlanetDetailWidget::UpdateStageList(const TArray<int32>& StageIDs)
{
    ClearStageList();
    CreateStageWidgets(StageIDs);
}

void UNDPlanetDetailWidget::ClearStageList()
{
    if (StageScrollBox)
    {
        StageScrollBox->ClearChildren();
    }
    StageWidgets.Empty();
}

void UNDPlanetDetailWidget::CreateStageWidgets(const TArray<int32>& StageIDs)
{
    if (!StageScrollBox || !StageInfoWidgetClass)
        return;

    UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance());
    if (!GameInstance)
        return;

    for (int32 StageID : StageIDs)
    {
        FStageInfo StageInfo = GameInstance->GetStageInfo(StageID);
        
        UNDStageInfoWidget* StageWidget = CreateWidget<UNDStageInfoWidget>(this, StageInfoWidgetClass);
        if (StageWidget)
        {
            StageWidget->SetStageInfo(StageInfo);
            StageScrollBox->AddChild(StageWidget);
            StageWidgets.Add(StageWidget);
        }
    }
}

void UNDPlanetDetailWidget::OnBackButtonClicked()
{
    if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        if (UNDEventManager* EventManager = GameInstance->GetEventManager())
        {
            EventManager->TriggerPlanetZoomOut();
        }
    }

    RemoveFromParent();
}