// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pattern/NDPoolableComponent.h"
#include "NDEnemy.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDEnemy();

	void ActivateEnemy(const FVector& SpawnLocation);
	void DeactivateEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	float DetectionRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MovementSpeed = 300.f;

	UPROPERTY()
	class ACharacter* PlayerCharacter;  // 플레이어 캐릭터 참조

	UPROPERTY(VisibleAnywhere)
	class UNDPoolableComponent* PoolableComponent;

	void ChasePlayer();
	bool IsPlayerInRange() const;

};
