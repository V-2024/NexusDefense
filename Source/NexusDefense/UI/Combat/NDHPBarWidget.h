// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UNDHPBarWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetMaxHP(float NewMaxHP) { MaxHP = NewMaxHP; }

	void UpdateHPBar(float CurrentHP);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	float MaxHP;
};
