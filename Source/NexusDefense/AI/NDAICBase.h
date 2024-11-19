// NDAICBase.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy/NDEnemyBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "NDAICBase.generated.h"

// AI Behavior State를 표현하는 새로운 enum
UENUM(BlueprintType)
enum class EAIBehaviorState : uint8
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

    // Enemy의 상태를 확인하는 helper 함수
    bool CanPerformAction() const;
    
protected:
    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void UpdateBehaviorState();
    void PursuitPlayer();
    void AttackPlayer();
    void FindPlayerCharacters();
    void UpdateTargetCharacter();

    // Enemy의 현재 상태를 가져오는 함수
    EEnemyState GetEnemyState() const;
    class ANDEnemyBase* GetControlledEnemy() const;

public:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float PursuitRadius;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float AttackRadius;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    EAIBehaviorState CurrentBehaviorState;

    ACharacter* TargetCharacter;
    ACharacter* ClosestCharacter;
    TArray<ACharacter*> PlayerCharacters;
    float ClosestDistance;
};