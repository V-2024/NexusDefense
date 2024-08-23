#include "NDEffectManager.h"
#include "NDObjectPoolManager.h"
#include "Particles/ParticleSystemComponent.h"

ANDEffectManager::ANDEffectManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ANDEffectManager::Initialize(ANDObjectPoolManager* PoolManager)
{
    ObjectPoolManager = PoolManager;
}

void ANDEffectManager::BeginPlay()
{
    Super::BeginPlay();
}

void ANDEffectManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateActiveEffects(DeltaTime);
}

void ANDEffectManager::PlayEffect(UParticleSystem* EffectTemplate, const FVector& Location, const FRotator& Rotation, float Duration)
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

void ANDEffectManager::StopEffect(UParticleSystemComponent* EffectComponent)
{
    if (EffectComponent)
    {
        EffectComponent->Deactivate();
        ActiveEffects.Remove(EffectComponent);
        ObjectPoolManager->ReturnParticleToPool(EffectComponent);
    }
}

void ANDEffectManager::UpdateActiveEffects(float DeltaTime)
{
    // �ʿ��� ��� ���⿡ Ȱ�� ȿ�� ������Ʈ ������ �߰��մϴ�.
}

void ANDEffectManager::SetWeatherEffect(UParticleSystem* WeatherEffect)
{
    // ���� ȿ�� ����
}

void ANDEffectManager::UpdateDayNightCycle(float TimeOfDay)
{
    // �־� ����Ŭ ������Ʈ ����
}