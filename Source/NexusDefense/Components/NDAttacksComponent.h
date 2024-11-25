
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NDCombatTypes.h"
#include "DamageSystem/ND_S_AttackInfo.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "NDAttacksComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttackHit, AActor*, HitActor, const FND_S_AttackInfo&, AttackInfo);

UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDAttacksComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNDAttacksComponent();

    // ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteAttack(EAttackTraceType TraceType, const FND_S_AttackInfo& AttackInfo, float Radius, float Length = 0.0f);

protected:
    virtual void BeginPlay() override;

    // ���� ���� �̺�Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnAttackHit OnAttackHit;

private:
    // ������ ĳ���� ���۷���
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    // ���� Ÿ�Ժ� ó�� �Լ���
    bool DoSphereTrace(const FND_S_AttackInfo& AttackInfo, float Radius, float Length);
    bool DoLineTrace(const FND_S_AttackInfo& AttackInfo, float Length);
    bool DoOverlapping(const FND_S_AttackInfo& AttackInfo, float Radius);

    // ���� ���� ó�� �Լ�
    void ProcessHit(AActor* HitActor, const FND_S_AttackInfo& AttackInfo);

    // ����� ����� ����
    UPROPERTY(EditDefaultsOnly, Category = "Debug")
    bool bDrawDebug = false;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (EditCondition = "bDrawDebug"))
    float DebugDrawTime = 2.0f;
};
