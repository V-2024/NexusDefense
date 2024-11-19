// NDPlanetIconWidget.cpp
#include "UI/MainUI/NDPlanetIconWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"

void UNDPlanetIconWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(PlanetButton)
    {
        PlanetButton->OnClicked.AddDynamic(this, &UNDPlanetIconWidget::OnPlanetButtonClicked);
    }

    bIsSelected = false;
    UpdateVisuals();
}

void UNDPlanetIconWidget::SetPlanetInfo(const FPlanetInfo& InPlanetInfo)
{
    PlanetInfo = InPlanetInfo;
    bIsUnlocked = PlanetInfo.bIsUnlocked;

    UpdateVisuals();
    SetPosition(PlanetInfo.Position);
}

void UNDPlanetIconWidget::UpdateVisuals()
{
    if(PlanetImage)
    {
        PlanetImage->SetBrushFromTexture(PlanetInfo.PlanetImage);
        
        // 잠금 상태에 따른 시각적 효과
        if(!bIsUnlocked)
        {
            PlanetImage->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
        }
        else
        {
            PlanetImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    if(PlanetNameText)
    {
        PlanetNameText->SetText(FText::FromName(PlanetInfo.PlanetName));
    }

    if(SelectionRing)
    {
        SelectionRing->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void UNDPlanetIconWidget::SetPosition(const FVector2D& NewPosition)
{
    if(UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot))
    {
        CanvasSlot->SetPosition(NewPosition);
    }
}

void UNDPlanetIconWidget::OnPlanetButtonClicked()
{
    if(!bIsUnlocked)
        return;

    if(UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        if(UNDEventManager* EventManager = GameInstance->GetEventManager())
        {
            EventManager->TriggerPlanetZoomIn(PlanetInfo);
        }
    }

    bIsSelected = true;
    UpdateVisuals();
    PlayZoomInAnimation();
}

void UNDPlanetIconWidget::PlayZoomInAnimation()
{
    if(ZoomInAnim)
    {
        PlayAnimation(ZoomInAnim);
    }
}

void UNDPlanetIconWidget::PlayZoomOutAnimation()
{
    if(ZoomOutAnim)
    {
        PlayAnimation(ZoomOutAnim);
    }
}

void UNDPlanetIconWidget::PlayFadeOutAnimation()
{
    if(FadeOutAnim)
    {
        PlayAnimation(FadeOutAnim);
    }
}

void UNDPlanetIconWidget::PlayHighlightAnimation()
{
    if(HighlightAnim)
    {
        PlayAnimation(HighlightAnim);
    }
}

void UNDPlanetIconWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    if(bIsUnlocked && !bIsSelected)
    {
        PlayHighlightAnimation();
    }
}

void UNDPlanetIconWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    if(bIsUnlocked && !bIsSelected)
    {
        // 하이라이트 애니메이션 역재생
        if(HighlightAnim)
        {
            PlayAnimation(HighlightAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse);
        }
    }
}

void UNDPlanetIconWidget::SetUnlockedState(bool bNewUnlocked)
{
    bIsUnlocked = bNewUnlocked;
    UpdateVisuals();
}