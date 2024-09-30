// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI/NDStageSelectWidget.h"
#include "GameInstance/NDGameInstance.h"
#include "UI/MainUI/NDPlanetWidget.h"
#include "UI/MainUI/NDPlanetDetailWidget.h"
#include "Stages/FPlanetInfo.h"



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
    if (GameInstance && StarSystemCanvas && PlanetWidgetClass)
    {
        TArray<FPlanetInfo> PlanetInfos = GameInstance->GetPlanetInfos();
        for (int32 i = 0; i < PlanetInfos.Num(); ++i)
        {
            UNDPlanetWidget* PlanetWidget = CreateWidget<UNDPlanetWidget>(this, PlanetWidgetClass);
            if (PlanetWidget)
            {
                PlanetWidget->SetPlanetInfo(PlanetInfos[i]);
                PlanetWidget->SetPlanetIndex(i);
                StarSystemCanvas->AddChild(PlanetWidget);
                PlanetWidgets.Add(PlanetWidget);

                // 행성 위치 설정 (원형 배치 등)
                // PlanetWidget->SetRenderTransform(...);
            }
        }
    }
}

void UNDStageSelectWidget::UpdatePlanetStates()
{
    // GameInstance에서 행성 상태 정보를 가져와 각 PlanetWidget 업데이트
    if (GameInstance)
    {
        for (UNDPlanetWidget* PlanetWidget : PlanetWidgets)
        {
            bool bIsUnlocked = GameInstance->IsPlanetUnlocked(PlanetWidget->GetPlanetIndex());
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

void UNDStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UNDGameInstance>(GetGameInstance());


    InitializePlanets();
    UpdatePlanetStates();
}

void UNDStageSelectWidget::NativeDestruct()
{
    Super::NativeDestruct();
}


void UNDStageSelectWidget::BackToMainMenu()
{
    if (GameInstance)
    {
        GameInstance->ReturnToMainMenu();
    }
}

void UNDStageSelectWidget::ZoomToPlanet(int32 PlanetIndex)
{
    if (PlanetDetailWidget && GameInstance)
    {
        FPlanetInfo PlanetInfo = GameInstance->GetPlanetInfos()[PlanetIndex];
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




