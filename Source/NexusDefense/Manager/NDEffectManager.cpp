#include "NDEffectManager.h"
#include "NDObjectPoolManager.h"
#include "Particles/ParticleSystemComponent.h"

UNDEffectManager::UNDEffectManager()
{

}

void UNDEffectManager::Initialize(UNDObjectPoolManager* PoolManager)
{
    ObjectPoolManager = PoolManager;
}


void UNDEffectManager::PlayEffect(UParticleSystem* EffectTemplate, const FVector& Location, const FRotator& Rotation, float Duration)
{
    if (EffectTemplate && ObjectPoolManager)
    {
        UParticleSystemComponent* EffectComponent = Cast<UParticleSystemComponent>(ObjectPoolManager->GetPooledObject(UParticleSystemComponent::StaticClass()));
        if (EffectComponent)
        {
            EffectComponent->SetTemplate(EffectTemplate);
            EffectComponent->SetWorldLocationAndRotation(Location, Rotation);
            EffectComponent->Activate();
            ActiveEffects.Add(EffectComponent);

            if (Duration > 0.0f)
            {
                FTimerHandle TimerHandle;
                GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, EffectComponent]()
                    {
                        StopEffect(EffectComponent);
                    }, Duration, false);
            }
        }
    }
}

void UNDEffectManager::StopEffect(UParticleSystemComponent* EffectComponent)
{
    if (EffectComponent)
    {
        EffectComponent->Deactivate();
        ActiveEffects.Remove(EffectComponent);
        ObjectPoolManager->ReturnParticleToPool(EffectComponent);
    }
}

void UNDEffectManager::UpdateActiveEffects(float DeltaTime)
{
    // �ʿ��� ��� ���⿡ Ȱ�� ȿ�� ������Ʈ ������ �߰��մϴ�.
}

void UNDEffectManager::SetWeatherEffect(UParticleSystem* WeatherEffect)
{
    // ���� ȿ�� ����
}

void UNDEffectManager::UpdateDayNightCycle(float TimeOfDay)
{
    // �־� ����Ŭ ������Ʈ ����
}