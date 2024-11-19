// NDStageInfoWidget.cpp
#include "UI/MainUI/NDStageInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"

void UNDStageInfoWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StageButton)
    {
        StageButton->OnClicked.AddDynamic(this, &UNDStageInfoWidget::OnStageButtonClicked);
        StageButton->OnHovered.AddDynamic(this, &UNDStageInfoWidget::OnHovered);
        StageButton->OnUnhovered.AddDynamic(this, &UNDStageInfoWidget::OnUnhovered);
    }
}

void UNDStageInfoWidget::SetStageInfo(const FStageInfo& InStageInfo)
{
    StageInfo = InStageInfo;
    UpdateVisuals();
}

void UNDStageInfoWidget::UpdateVisuals()
{
    if (StageIcon)
    {
        StageIcon->SetBrushFromTexture(StageInfo.Icon);
    }

    if (StageNameText)
    {
        StageNameText->SetText(FText::FromString(StageInfo.Name));
    }

    UpdateLockStatus(StageInfo.bIsUnlocked);
    UpdateClearedStatus(StageInfo.bIsCompleted);
}

void UNDStageInfoWidget::UpdateLockStatus(bool bIsUnlocked)
{
    if (LockOverlay)
    {
        LockOverlay->SetVisibility(bIsUnlocked ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
    }

    if (StageButton)
    {
        StageButton->SetIsEnabled(bIsUnlocked);
    }
}

void UNDStageInfoWidget::UpdateClearedStatus(bool bIsCleared)
{
    if (ClearedIcon)
    {
        ClearedIcon->SetVisibility(bIsCleared ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void UNDStageInfoWidget::OnStageButtonClicked()
{
    if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        if (UNDEventManager* EventManager = GameInstance->GetEventManager())
        {
            // 스테이지 선택 이벤트 발생
            EventManager->TriggerStageInfoUpdated(StageInfo);
        }
    }
}

void UNDStageInfoWidget::OnHovered()
{
    if (HoverAnimation)
    {
        PlayAnimation(HoverAnimation);
    }
}

void UNDStageInfoWidget::OnUnhovered()
{
    if (HoverAnimation)
    {
        PlayAnimation(HoverAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
    }
}