// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NDComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	UNDComboActionData();
public:
	UPROPERTY(EditAnywhere, Category = "Name")
	FString MontageSectionPrefix;

	UPROPERTY(EditAnywhere, Category = "Name")
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = "Name")
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = "ComboData")
	TArray<float> EffectiveFrameCount;

	UPROPERTY(EditAnywhere, Category = "ComboDamages")
	TArray<float> ComboDamages;
};
