// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Amount);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.f;

};
