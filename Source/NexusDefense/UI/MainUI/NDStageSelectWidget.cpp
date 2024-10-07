// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDStageSelectWidget.h"
#include "GameInstance/NDGameInstance.h"
#include "UI/MainUI/NDPlanetWidget.h"
#include "UI/MainUI/NDPlanetDetailWidget.h"
#include "Components/CanvasPanel.h"
#include "Manager/NDStageManager.h"



void UNDStageSelectWidget::SelectPlanet(int32 PlanetIndex)
{
    if (PlanetIndex >= 0 && PlanetIndex < PlanetWidgets.Num())
    {
        CurrentSelectedPlanetIndex = PlanetIndex;
        ZoomToPlanet(PlanetIndex);
    }
}

void UNDStageSelectWidget::InitializePlanets()
{
    // GameInstance에서 행성 정보를 가져와 동적으로 PlanetWidgets 생성
    if (StageManager && StarSystemCanvas && PlanetWidgetClass)
    {
        //TArray<FPlanetInfo> PlanetInfos = GameInstance->TriggerGetPlanetInfosEvent();
        PlanetInfos = StageManager->GetPlanetInfos();
        for (int32 i = 0; i < PlanetInfos.Num(); ++i)
        {
            UNDPlanetWidget* PlanetWidget = CreateWidget<UNDPlanetWidget>(this, PlanetWidgetClass);
            if (PlanetWidget)
            {
                PlanetWidget->SetPlanetInfo(PlanetInfos[i]);
                PlanetWidget->SetPlanetIndex(i);
                
                StarSystemCanvas->AddChild(PlanetWidget);
                PlanetWidgets.Add(PlanetWidget);

                // 원형 배치 로직
                FVector2D Center(StarSystemCanvas->GetCachedGeometry().GetLocalSize() / 2);
                float Radius = FMath::Min(Center.X, Center.Y) * 0.8f;
                float Angle = (2 * PI * i) / PlanetInfos.Num();
                FVector2D Position = Center + FVector2D(FMath::Cos(Angle), FMath::Sin(Angle)) * Radius;
                PlanetWidget->SetRenderTranslation(Position);
            }
        }
    }
}

void UNDStageSelectWidget::UpdatePlanetStates()
{
    // GameInstance에서 행성 상태 정보를 가져와 각 PlanetWidget 업데이트
    if (StageManager)
    {
        for (UNDPlanetWidget* PlanetWidget : PlanetWidgets)
        {
            bool bIsUnlocked = StageManager->IsPlanetUnlocked(PlanetWidget->GetPlanetIndex());
            PlanetWidget->SetUnlocked(bIsUnlocked);
        }
    }
}

void UNDStageSelectWidget::OnBackButtonClicked()
{
    if (bIsZoomedIn)
    {
        ZoomOutToPlanets();
    }
    else
    {
        BackToMainMenu();
    }
}

void UNDStageSelectWidget::OnPlanetClicked(int32 PlanetIndex)
{
    if (PlanetInfos.IsValidIndex(PlanetIndex))
	{
		if (PlanetInfos[PlanetIndex].bIsUnlocked)
		{
            PlanetDetailWidget->SetPlanetInfo(PlanetWidgets[PlanetIndex]->GetPlanetInfo());
            PlanetDetailWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UNDStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //GameInstance = Cast<UNDGameInstance>(GetGameInstance());

    StageManager = GetGameInstance<UNDGameInstance>()->GetStageManager();

    InitializePlanets();
    UpdatePlanetStates();

    if (PlanetDetailWidget)
    {
        PlanetDetailWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UNDStageSelectWidget::NativeDestruct()
{
    Super::NativeDestruct();
}


void UNDStageSelectWidget::BackToMainMenu()
{
    /*if (GameInstance)
    {
        GameInstance->ReturnToMainMenu();
    }*/
}

void UNDStageSelectWidget::ZoomToPlanet(int32 PlanetIndex)
{
    if (PlanetDetailWidget && StageManager)
    {
        FPlanetInfo PlanetInfo = StageManager->GetPlanetInfos()[PlanetIndex];

        //PlanetWidgets[PlanetIndex]->SetVisibility(ESlateVisibility::Hidden);

        PlanetDetailWidget->SetPlanetInfo(PlanetInfo);
        PlanetDetailWidget->SetVisibility(ESlateVisibility::Visible);

        // Play Zoom In Animation
        // ...

        bIsZoomedIn = true;
    }
}

void UNDStageSelectWidget::ZoomOutToPlanets()
{
    if (PlanetDetailWidget)
    {
        PlanetDetailWidget->SetVisibility(ESlateVisibility::Hidden);

        // 줌 아웃 애니메이션 실행
        // ...

        bIsZoomedIn = false;
        CurrentSelectedPlanetIndex = -1;
    }
}




