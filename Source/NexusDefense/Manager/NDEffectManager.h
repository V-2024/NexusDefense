#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDEffectManager.generated.h"

class ANDObjectPoolManager;
class UParticleSystemComponent;

UCLASS()
class NEXUSDEFENSE_API ANDEffectManager : public AActor
{
    GENERATED_BODY()

public:
    ANDEffectManager();
    static ANDEffectManager* GetInstance();

    void Initialize(ANDObjectPoolManager* PoolManager);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayEffect(UParticleSystem* EffectTemplate, const FVector& Location, const FRotator& Rotation, float Duration = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void StopEffect(UParticleSystemComponent* EffectComponent);

    void SetWeatherEffect(UParticleSystem* WeatherEffect);
    void UpdateDayNightCycle(float TimeOfDay);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY()
    ANDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    TArray<UParticleSystemComponent*> ActiveEffects;

    void UpdateActiveEffects(float DeltaTime);
};