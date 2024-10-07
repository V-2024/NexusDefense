#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDEffectManager.generated.h"

class UNDObjectPoolManager;
class UParticleSystemComponent;

UCLASS()
class NEXUSDEFENSE_API UNDEffectManager : public UObject
{
    GENERATED_BODY()

public:
    UNDEffectManager();

    void Initialize(UNDObjectPoolManager* PoolManager);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayEffect(UParticleSystem* EffectTemplate, const FVector& Location, const FRotator& Rotation, float Duration = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void StopEffect(UParticleSystemComponent* EffectComponent);

    void SetWeatherEffect(UParticleSystem* WeatherEffect);
    void UpdateDayNightCycle(float TimeOfDay);


private:
    UPROPERTY()
    UNDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    TArray<UParticleSystemComponent*> ActiveEffects;

    void UpdateActiveEffects(float DeltaTime);
};