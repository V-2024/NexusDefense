// NDPlanetIconWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/NDGameTypes.h"
#include "Stages/FPlanetInfo.h"
#include "NDPlanetIconWidget.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDPlanetIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlanetInfo(const FPlanetInfo& InPlanetInfo);
	const FPlanetInfo& GetPlanetInfo() const { return PlanetInfo; }
    
	// 애니메이션 관련 함수들
	void PlayZoomInAnimation();
	void PlayZoomOutAnimation();
	void PlayFadeOutAnimation();
	void PlayHighlightAnimation();
    
	// 위치 설정
	void SetPosition(const FVector2D& NewPosition);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// 바인딩할 UI 컴포넌트들
	UPROPERTY(meta = (BindWidget))
	class UButton* PlanetButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* PlanetImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectionRing;  // 선택 시 표시될 링 이미지

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlanetNameText;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ConnectionLinesPanel;  // 행성 간 연결선을 그릴 패널

	// 애니메이션
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ZoomInAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ZoomOutAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* HighlightAnim;

private:
	UPROPERTY()
	FPlanetInfo PlanetInfo;

	bool bIsSelected;
	bool bIsUnlocked;

	UFUNCTION()
	void OnPlanetButtonClicked();

	void UpdateVisuals();
	void UpdateConnectionLines();
	void SetUnlockedState(bool bNewUnlocked);
};