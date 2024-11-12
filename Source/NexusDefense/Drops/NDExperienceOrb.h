// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drops/NDItem.h"
#include "Pattern/NDExperienceComponent.h"
#include "NDExperienceOrb.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API ANDExperienceOrb : public ANDItem
{
	GENERATED_BODY()
	
public:
    ANDExperienceOrb();

protected:
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float ExperienceAmount = 20.f;
};
