// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDStageButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UNDStageButtonWidget::SetStageID(int32 InStageID)
{
    StageID = InStageID;
    UpdateStageState();
}

void UNDStageButtonWidget::SetStageInfo(const FStageInfo& Info)
{
    StageInfo = Info;

    if (StageNameText)
    {
        StageNameText->SetText(FText::FromString(StageInfo.Name));
    }

    if (StageIcon)
    {
        StageIcon->SetBrushFromTexture(StageInfo.Icon);
    }

    UpdateStageState();
    OnStageInfoUpdated();
}

void UNDStageButtonWidget::UpdateStageState()
{
    if (1) //GameInstance)
    {
        //bool bIsUnlocked = GameInstance->IsStageUnlocked(StageID);
        //bool bIsCompleted = GameInstance->IsStageCompleted(StageID);

        // 스테이지의 잠금 상태나 완료 상태에 따라 버튼의 외관을 업데이트
        if (StageButton)
        {
            StageButton->SetIsEnabled(bIsUnlocked);
        }

        // 추가적인 시각적 피드백 (예: 아이콘 변경, 색상 변경 등)
        // ...

        OnStageInfoUpdated();
    }
}


void UNDStageButtonWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //GameInstance = Cast<UNDGameInstance>(GetGameInstance());

    if (StageButton)
    {
        StageButton->OnClicked.AddDynamic(this, &UNDStageButtonWidget::OnStageButtonClicked);
    }
}

void UNDStageButtonWidget::OnStageButtonClicked()
{
    //if (GameInstance)
    //{
    //    //GameInstance->GetEventManager()
    //    //GameInstance->StartStage(StageID);
    //}
}
