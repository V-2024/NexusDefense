
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

    // 공격 실행 함수
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteAttack(EAttackTraceType TraceType, const FND_S_AttackInfo& AttackInfo, float Radius, float Length = 0.0f);

protected:
    virtual void BeginPlay() override;

    // 공격 적중 이벤트
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnAttackHit OnAttackHit;

private:
    // 소유자 캐릭터 레퍼런스
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    // 공격 타입별 처리 함수들
    bool DoSphereTrace(const FND_S_AttackInfo& AttackInfo, float Radius, float Length);
    bool DoLineTrace(const FND_S_AttackInfo& AttackInfo, float Length);
    bool DoOverlapping(const FND_S_AttackInfo& AttackInfo, float Radius);

    // 공격 적중 처리 함수
    void ProcessHit(AActor* HitActor, const FND_S_AttackInfo& AttackInfo);

    // 디버그 드로잉 설정
    UPROPERTY(EditDefaultsOnly, Category = "Debug")
    bool bDrawDebug = false;

    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (EditCondition = "bDrawDebug"))
    float DebugDrawTime = 2.0f;
};
