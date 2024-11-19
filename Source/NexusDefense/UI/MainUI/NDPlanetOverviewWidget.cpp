// NDPlanetOverviewWidget.cpp
#include "UI/MainUI/NDPlanetOverviewWidget.h"
#include "UI/MainUI/NDPlanetIconWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameInstance/NDGameInstance.h"
#include "Manager/NDEventManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UNDPlanetOverviewWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // GameInstance에서 행성 데이터를 가져와 초기화
    if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        TArray<FPlanetInfo> Planets = GameInstance->GetPlanets();
        CreatePlanetIcons(Planets);
        
        // 이벤트 매니저에 줌 이벤트 바인딩
        if (UNDEventManager* EventManager = GameInstance->GetEventManager())
        {
            EventManager->OnPlanetZoomIn.AddUObject(this, &UNDPlanetOverviewWidget::HandlePlanetZoomIn);
            EventManager->OnPlanetZoomOut.AddUObject(this, &UNDPlanetOverviewWidget::HandlePlanetZoomOut);
        }
    }

    // 화면 크기 변경 시 행성 위치 업데이트를 위한 델리게이트 바인딩
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            LayoutTimerHandle,
            this,
            &UNDPlanetOverviewWidget::UpdatePlanetPositions,
            0.1f,
            false
        );
    }
}

void UNDPlanetOverviewWidget::NativeDestruct()
{
    Super::NativeConstruct();

    if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        TArray<FPlanetInfo> Planets = GameInstance->GetPlanets();
        CreatePlanetIcons(Planets);
        
        if (UNDEventManager* EventManager = GameInstance->GetEventManager())
        {
            EventManager->OnPlanetZoomIn.AddUObject(this, &UNDPlanetOverviewWidget::HandlePlanetZoomIn);
            EventManager->OnPlanetZoomOut.AddUObject(this, &UNDPlanetOverviewWidget::HandlePlanetZoomOut);
        }
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(LayoutTimerHandle, this, 
            &UNDPlanetOverviewWidget::UpdatePlanetPositions, 0.1f, false);
    }
}

void UNDPlanetOverviewWidget::CreatePlanetIcons(const TArray<FPlanetInfo>& Planets)
{
    if (!PlanetCanvas || !PlanetIconClass)
        return;

    // 기존 행성 아이콘들 제거
    PlanetCanvas->ClearChildren();
    PlanetIcons.Empty();

    // 새로운 행성 아이콘들 생성
    for (const FPlanetInfo& PlanetInfo : Planets)
    {
        UNDPlanetIconWidget* PlanetIcon = CreateWidget<UNDPlanetIconWidget>(this, PlanetIconClass);
        if (PlanetIcon)
        {
            PlanetIcon->SetPlanetInfo(PlanetInfo);
            
            UCanvasPanelSlot* CanvasSlot = PlanetCanvas->AddChildToCanvas(PlanetIcon);
            if (CanvasSlot)
            {
                // 초기 위치와 크기 설정
                CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
                CanvasSlot->SetSize(FVector2D(100.0f, 100.0f)); // 기본 크기, 필요에 따라 조정
                CanvasSlot->SetPosition(PlanetInfo.Position);
            }

            PlanetIcons.Add(PlanetIcon);
            DrawConnectionLine(PlanetInfo);
        }
    }
}

void UNDPlanetOverviewWidget::UpdatePlanetPositions()
{
    if (!PlanetCanvas)
        return;

    FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
    FGeometry CanvasGeometry = PlanetCanvas->GetCachedGeometry();
    FVector2D CanvasSize = CanvasGeometry.GetLocalSize();

    // 각 행성 아이콘의 위치 업데이트
    for (UNDPlanetIconWidget* PlanetIcon : PlanetIcons)
    {
        if (PlanetIcon)
        {
            const FPlanetInfo& PlanetInfo = PlanetIcon->GetPlanetInfo();
            FVector2D NewPosition = PlanetInfo.Position * CanvasSize;
            PlanetIcon->SetPosition(NewPosition);
        }
    }

    // 연결선 업데이트
    UpdateConnectionLines();
}

void UNDPlanetOverviewWidget::DrawConnectionLine(const FPlanetInfo& PlanetInfo)
{
    // 연결선을 그리기 위한 로직
    // 여기서는 간단한 예시만 제공합니다
    // 실제 구현 시에는 더 복잡한 로직이 필요할 수 있습니다

    if (!PlanetCanvas || !ConnectionLineClass)
        return;

    // 연결된 행성들 간에 선 그리기
    for (int32 StageID : PlanetInfo.StageIDs)
    {
        // 연결된 다른 행성 찾기
        for (UNDPlanetIconWidget* OtherPlanet : PlanetIcons)
        {
            if (OtherPlanet && OtherPlanet->GetPlanetInfo().StageIDs.Contains(StageID))
            {
                // 연결선 위젯 생성
                UUserWidget* ConnectionLine = CreateWidget<UUserWidget>(this, ConnectionLineClass);
                if (ConnectionLine)
                {
                    UCanvasPanelSlot* LineSlot = PlanetCanvas->AddChildToCanvas(ConnectionLine);
                    ConnectionLines.Add(ConnectionLine);
                    // 연결선의 위치와 회전 설정
                    UpdateConnectionLineTransform(LineSlot, PlanetInfo.Position, OtherPlanet->GetPlanetInfo().Position);
                }
            }
        }
    }
}

void UNDPlanetOverviewWidget::UpdateConnectionLines()
{
    // 모든 연결선 업데이트
    for (UUserWidget* ConnectionLine : ConnectionLines)
    {
        if (UCanvasPanelSlot* LineSlot = Cast<UCanvasPanelSlot>(ConnectionLine->Slot))
        {
            // 연결된 행성들의 현재 위치 가져오기
            // 이 부분은 연결 정보를 저장하는 방식에 따라 구현이 달라질 수 있습니다
            UpdateConnectionLineTransform(LineSlot, FVector2D::ZeroVector, FVector2D::ZeroVector);
        }
    }
}

void UNDPlanetOverviewWidget::UpdateConnectionLineTransform(UCanvasPanelSlot* LineSlot, const FVector2D& StartPos, const FVector2D& EndPos)
{
    if (!LineSlot)
        return;

    UWidget* ConnectionLine = LineSlot->Content;
    if (!ConnectionLine)
        return;

    // 두 점 사이의 거리와 각도 계산
    FVector2D Delta = EndPos - StartPos;
    float Distance = Delta.Size();
    float Angle = FMath::Atan2(Delta.Y, Delta.X);

    // 연결선 위젯의 Position과 Size 설정
    LineSlot->SetPosition((StartPos + EndPos) * 0.5f);
    LineSlot->SetSize(FVector2D(Distance, 2.0f)); // 선의 두께는 2픽셀

    // 회전 설정
    ConnectionLine->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));  // 중심점 설정
    ConnectionLine->SetRenderTransformAngle(FMath::RadiansToDegrees(Angle));  // 각도 설정
}

void UNDPlanetOverviewWidget::HandlePlanetZoomIn(const FPlanetInfo& PlanetInfo)
{
    // 선택된 행성 외의 다른 행성들 페이드 아웃
    for (UNDPlanetIconWidget* PlanetIcon : PlanetIcons)
    {
        if (PlanetIcon && PlanetIcon->GetPlanetInfo().PlanetName != PlanetInfo.PlanetName)
        {
            PlanetIcon->PlayFadeOutAnimation();
        }
    }
}

void UNDPlanetOverviewWidget::HandlePlanetZoomOut()
{
    // 모든 행성 다시 표시
    for (UNDPlanetIconWidget* PlanetIcon : PlanetIcons)
    {
        if (PlanetIcon)
        {
            PlanetIcon->SetVisibility(ESlateVisibility::Visible);
            PlanetIcon->PlayZoomOutAnimation();
        }
    }
}

void UNDPlanetOverviewWidget::OnViewportSizeChanged(const FVector2D& NewViewportSize)
{
    UpdatePlanetPositions();
}

FReply UNDPlanetOverviewWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // 줌 레벨 조정
    float WheelDelta = InMouseEvent.GetWheelDelta();
    UpdateZoomLevel(WheelDelta);
    
    return FReply::Handled();
}

void UNDPlanetOverviewWidget::UpdateZoomLevel(float DeltaZoom)
{
    // 줌 레벨에 따른 행성 크기 조정
    CurrentZoomLevel = FMath::Clamp(CurrentZoomLevel + DeltaZoom * ZoomSpeed, MinZoomLevel, MaxZoomLevel);
    
    for (UNDPlanetIconWidget* PlanetIcon : PlanetIcons)
    {
        if (PlanetIcon)
        {
            UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PlanetIcon->Slot);
            if (CanvasSlot)
            {
                float NewSize = BaseIconSize * CurrentZoomLevel;
                CanvasSlot->SetSize(FVector2D(NewSize, NewSize));
            }
        }
    }
    
    UpdateConnectionLines();
}