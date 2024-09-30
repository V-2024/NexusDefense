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

        // ���������� ��� ���³� �Ϸ� ���¿� ���� ��ư�� �ܰ��� ������Ʈ
        if (StageButton)
        {
            StageButton->SetIsEnabled(bIsUnlocked);
        }

        // �߰����� �ð��� �ǵ�� (��: ������ ����, ���� ���� ��)
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
