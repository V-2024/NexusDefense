// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "NDAICBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Pursuit,
    Attack
};

UCLASS()
class NEXUSDEFENSE_API ANDAICBase : public AAIController
{
	GENERATED_BODY()
	
public:
    ANDAICBase();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void UpdateEnemyState();
    void PursuitPlayer();
    void AttackPlayer();
    void FindPlayerCharacters();
    void UpdateTargetCharacter();


public:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float PursuitRadius;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float AttackRadius;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    EEnemyState CurrentState;

    ACharacter* TargetCharacter;

    ACharacter* ClosestCharacter;

    TArray<ACharacter*> PlayerCharacters;

    float ClosestDistance;
};
