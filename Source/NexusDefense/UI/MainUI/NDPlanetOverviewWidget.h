#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FPlanetInfo.h"
#include "NDPlanetOverviewWidget.generated.h"

class UNDPlanetIconWidget;
class UCanvasPanel;
class UCanvasPanelSlot;

UCLASS()
class NEXUSDEFENSE_API UNDPlanetOverviewWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* PlanetCanvas;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UNDPlanetIconWidget> PlanetIconClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ConnectionLineClass;

	// Zoom settings
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MinZoomLevel = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MaxZoomLevel = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float BaseIconSize = 100.0f;

private:
	UPROPERTY()
	TArray<UNDPlanetIconWidget*> PlanetIcons;

	UPROPERTY()
	TArray<UUserWidget*> ConnectionLines;

	FTimerHandle LayoutTimerHandle;
	float CurrentZoomLevel = 1.0f;

	void CreatePlanetIcons(const TArray<FPlanetInfo>& Planets);
	void UpdatePlanetPositions();
	void DrawConnectionLine(const FPlanetInfo& PlanetInfo);
	void UpdateConnectionLines();
	void UpdateConnectionLineTransform(UCanvasPanelSlot* LineSlot, const FVector2D& StartPos, const FVector2D& EndPos);
	void HandlePlanetZoomIn(const FPlanetInfo& PlanetInfo);
	void HandlePlanetZoomOut();
	void OnViewportSizeChanged(const FVector2D& NewViewportSize);
	void UpdateZoomLevel(float DeltaZoom);
};