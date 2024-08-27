// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase/NDWidgetComponent.h"
#include "UI/UIBase/NDUserWidget.h"

void UNDWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UNDUserWidget* UserWidget = Cast<UNDUserWidget>(GetWidget());

	if (UserWidget)
	{
		UserWidget->SetOwningActor(GetOwner());
	}
}
