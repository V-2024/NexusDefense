// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/NDAITask.h"
#include "Components/NDHealthComponent.h"
#include "NDEnemy.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDEnemy();
	virtual void Tick(float DeltaTime) override;

	void ActivateEnemy(const FVector& SpawnLocation);
	void DeactivateEnemy();

	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetAttackRange() const { return AttackRange; }

	void ExecuteAIResult(const FNDAITask& CompletedTask);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UNDHealthComponent* HealthComponent;

	UFUNCTION()
	void OnDamageReceived(const FND_S_DamageInfo& DamageInfo);

private:
	//UPROPERTY(EditAnywhere, Category = "AI")
	//float DetectionRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MovementSpeed = 300.f;

	UPROPERTY()
	class ACharacter* PlayerCharacter;  // �÷��̾� ĳ���� ����

	UPROPERTY(VisibleAnywhere)
	class UNDPoolableComponent* PoolableComponent;

	//void ChasePlayer();
	//bool IsPlayerInRange() const;

};
