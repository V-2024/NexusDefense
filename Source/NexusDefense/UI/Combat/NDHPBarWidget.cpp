// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Combat/NDHPBarWidget.h"
#include "Components/ProgressBar.h"

UNDHPBarWidget::UNDHPBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHP = -1.0f;
}

void UNDHPBarWidget::UpdateHPBar(float CurrentHP)
{
	ensure(MaxHP > 0.0f);

	if (HPProgressBar)
	{
		HPProgressBar->SetPercent(CurrentHP / MaxHP);
	}
}

void UNDHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));

	ensure(HPProgressBar);
}