// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NDItemBase.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ANDItemBase();

protected:
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* CollisionSphere;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* ItemMesh;

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);
};
