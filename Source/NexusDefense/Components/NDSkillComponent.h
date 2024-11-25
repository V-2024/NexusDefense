
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NDCombatTypes.h"
#include "Combat/NDCombatData.h"
#include "NDSkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillExecuted, FName, SkillName, float, CoolTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillCooldownEnd, FName, SkillName);

UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class NEXUSDEFENSE_API UNDSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNDSkillComponent();

    // 스킬 실행 관련 함수들
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteSkill(FName SkillName);

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsSkillReady(FName SkillName) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetSkillCooldownRemaining(FName SkillName) const;

protected:
    virtual void BeginPlay() override;

    // 스킬 데이터 테이블 참조
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSoftObjectPtr<UDataTable> SkillDataTable;

    // 스킬 상태 맵
    UPROPERTY()
    TMap<FName, FSkillState> SkillStates;

    // 컴포넌트 레퍼런스들
    UPROPERTY()
    TWeakObjectPtr<ACharacter> OwnerCharacter;

    UPROPERTY()
    class UNDCombatComponent* CombatComponent;

    UPROPERTY()
    class UNDAttacksComponent* AttacksComponent;

    // 이벤트 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillExecuted OnSkillExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
    FOnSkillCooldownEnd OnSkillCooldownEnd;

private:
    // 쿨다운 관리 함수들
    void StartCooldown(FName SkillName, float CoolTime);

    UFUNCTION()
    void OnCooldownFinished(FName SkillName);
};

