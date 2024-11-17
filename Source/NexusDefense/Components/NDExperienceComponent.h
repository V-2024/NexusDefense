// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDExperienceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceChanged, float, NewExperience, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//��������Ʈ
	UPROPERTY(BlueprintAssignable)
	FOnExperienceChanged OnExperienceChanged;
	UPROPERTY(BlueprintAssignable, Category = "Experience")
	FOnLevelUp OnLevelUp;

	// ����ġ
	UFUNCTION(BlueprintCallable)
	void AddExperience(float Amount);
	UFUNCTION(BlueprintPure, Category = "Experience")
	float GetCurrentExperience() const { return CurrentExperience; }

	// ����
	UFUNCTION(BlueprintPure, Category = "Experience")
	int32 GetCurrentLevel() const { return CurrentLevel; }

	UFUNCTION(BlueprintPure, Category = "Experience")
	float GetRequiredExperience() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentExperience = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Experience")
	int32 CurrentLevel = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Experience")
	float BaseExperienceRequired = 100.f;

private:
	void CheckLevelUp();
};
