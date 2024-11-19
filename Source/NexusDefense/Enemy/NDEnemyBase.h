// NDEnemyBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/UIBase/NDEnemyWidgetInterface.h"
#include "Components/NDHealthComponent.h"
#include "Interfaces/NDEnemyInterface.h"
#include "NDEnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Spawning,
    Active,
    Attacking,
    Stunned,
    Dying,
    Inactive
};

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseHealth = 100.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage = 10.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackRange = 150.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectionRange = 1000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ThreatLevel = 1.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperiencePoints = 10;
};

UCLASS(Config=Game)
class NEXUSDEFENSE_API ANDEnemyBase : public ACharacter, public INDEnemyWidgetInterface, public INDEnemyInterface
{
    GENERATED_BODY()

public:
    ANDEnemyBase();

    // Interface Implementation
    virtual float GetThreatLevel() const override { return EnemyData.ThreatLevel; }
    virtual bool CanBeStunned() const override { return true; }
    virtual void ApplyStun(float Duration) override;
    virtual bool IsStunned() const override { return CurrentState == EEnemyState::Stunned; }
    virtual void OnSpawn() override;
    virtual void OnDeath() override;
    virtual void OnHit() override;
    virtual float GetAttackDamage() const override { return EnemyData.BaseDamage; }
    virtual float GetAttackRange() const override { return EnemyData.AttackRange; }
    virtual float GetDetectionRange() const override { return EnemyData.DetectionRange; }

    // Core Functions
    UFUNCTION(BlueprintCallable, Category = "Enemy")
    virtual void Activate();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    virtual void Deactivate();

    // Getters
    UFUNCTION(BlueprintCallable, Category = "Enemy")
    EEnemyState GetCurrentState() const { return CurrentState; }
    
    UFUNCTION(BlueprintPure, Category = "Enemy")
    int32 GetScoreValue() const { return EnemyData.ExperiencePoints; }

protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
    virtual void SetUpEnemyWidget(class UNDUserWidget* Widget) override;

    // Event Handlers
    UFUNCTION()
    virtual void OnHealthChanged(float NewHealth, float Delta);
    
    UFUNCTION()
    virtual void OnDamageTaken(const FND_S_DamageInfo& DamageInfo);
    
    UFUNCTION()
    virtual void OnDeathTriggered();

    // State Management
    virtual void SetEnemyState(EEnemyState NewState);

    // VFX & SFX
    virtual void PlayStateEffects(EEnemyState NewState);
    void PlaySpawnEffect() const;
    void PlayDestroyEffect() const;
    void PlaySpawnSound() const;
    void PlayDestroySound() const;
    void PlaySpawnAnimMontage();
    void PlayDeathAnimMontage();

protected:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UNDHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    TObjectPtr<class UNDWidgetComponent> HPBar;

    // State
    UPROPERTY()
    EEnemyState CurrentState;

    // Data
    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Data")
    FEnemyData EnemyData;

    // Effects
    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Effects")
    UParticleSystem* SpawnEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Effects")
    UParticleSystem* DestroyEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Sounds")
    USoundBase* SpawnSound;

    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Sounds")
    USoundBase* DestroySound;

    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Animation")
    UAnimMontage* SpawnAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Enemy|Animation")
    UAnimMontage* DeathAnimMontage;

private:
    bool bIsActive;
    FTimerHandle StunTimerHandle;
    void SetupComponents();

    UPROPERTY()
    class UNDEventManager* EventManager;
};