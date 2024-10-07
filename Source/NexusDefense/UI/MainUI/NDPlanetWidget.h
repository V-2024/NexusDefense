 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stages/FPlanetInfo.h"
#include "NDPlanetWidget.generated.h"


UCLASS()
class NEXUSDEFENSE_API UNDPlanetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlanetInfo(const FPlanetInfo& InPlanetInfo);
	void SetPlanetIndex(int32 InPlanetIndex);
	void SetUnlocked(bool bInUnlocked);
	int32 GetPlanetIndex() const { return PlanetIndex; }

	FORCEINLINE FPlanetInfo GetPlanetInfo() const { return PlanetInfo; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Planet")
	void OnPlanetInfoUpdated();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPlanetButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* PlanetButton;

	UPROPERTY(BlueprintReadOnly, Category = "Planet")
	FPlanetInfo PlanetInfo;

	UPROPERTY(BlueprintReadOnly, Category = "Planet")
	int32 PlanetIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Planet")
	class UImage* PlanetImage;

	UPROPERTY(BlueprintReadOnly, Category = "Planet")
	class UTextBlock* PlanetNameText;
};
