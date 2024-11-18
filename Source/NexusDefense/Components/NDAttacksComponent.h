// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystem/ND_S_AttackInfo.h"
#include "Components/NDHealthComponent.h"
#include "Combat/NDCombatTypes.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NDAttacksComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDAttacksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNDAttacksComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool ExecuteAttack(EAttackTraceType TraceType, const FND_S_AttackInfo& AttackInfo, float Radius, float Length = 0.0f);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;	

	bool DoSphereTrace(const FND_S_AttackInfo& AttackInfo, float Radius, float Length);
	bool DoLineTrace(const FND_S_AttackInfo& AttackInfo, float Length);
	bool DoOverlapping(const FND_S_AttackInfo& AttackInfo, float Radius);
};
