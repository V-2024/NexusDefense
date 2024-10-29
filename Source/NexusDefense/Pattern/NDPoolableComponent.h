// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/NDPoolableInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NDPoolableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDPoolableComponent : public UActorComponent, public INDPoolableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNDPoolableComponent();

	virtual void ActivatePoolable() override;
	virtual void DeactivatePoolable() override;
	virtual bool IsPoolableActive() const override;

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void ReturnToPool();

	DECLARE_MULTICAST_DELEGATE(FOnPoolableActivated)
	DECLARE_MULTICAST_DELEGATE(FOnPoolableDeactivated)

	FOnPoolableActivated OnPoolableActivated;
	FOnPoolableDeactivated OnPoolableDeactivated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool bIsActive;

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	float AutoDeactivateTime = 5.0f;

	FTimerHandle DeactivationTimerHandle;
		
};
