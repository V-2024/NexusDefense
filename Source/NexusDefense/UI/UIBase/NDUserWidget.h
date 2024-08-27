// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDUserWidget.generated.h"


UCLASS()
class NEXUSDEFENSE_API UNDUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwningActor(AActor* InActor)	{ OwningActor = InActor; }
	FORCEINLINE AActor* GetOwningActor() const			{ return OwningActor.Get(); }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
	
};
