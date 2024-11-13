// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDExperienceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperienceChanged, float, NewExperience);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void AddExperience(float Amount);

	UFUNCTION(BlueprintPure, Category = "Experience")
	float GetCurrentExperience() const { return CurrentExperience; }

	UPROPERTY(BlueprintAssignable)
	FOnExperienceChanged OnExperienceChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentExperience = 0.f;
};
