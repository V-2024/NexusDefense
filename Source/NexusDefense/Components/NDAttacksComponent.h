// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystem/ND_S_AttackInfo.h"
#include "DamageSystem/ND_C_DamageSystem.h"
#include "NDAttacksComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDAttacksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNDAttacksComponent();

private:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool PrimaryMeleeAttack(const FND_S_AttackInfo& AttackInfo, float Radius, float Length);

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;	
};
