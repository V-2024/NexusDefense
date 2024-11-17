// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drops/NDItem.h"
#include "Components/NDHealthComponent.h"
//����� ��ƼŬ
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "NDHealthItem.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDHealthItem : public ANDItem
{
	GENERATED_BODY()
	
protected:
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float HealAmount = 25.f;

    UNDHealthComponent* GetHealthComponent(AActor* Target) const;

    // ���� ȿ�� ���� �Լ�
    virtual void ApplyHealing(AActor* Target);

    // ȿ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    USoundCue* HealSound;
    // ��ƼŬ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* HealEffect;
};
