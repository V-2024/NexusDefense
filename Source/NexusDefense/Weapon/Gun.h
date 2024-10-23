// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/NDObjectPoolManager.h"
#include "Ammo/NDBullet.h"
#include "Gun.generated.h"

UCLASS()
class NEXUSDEFENSE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();
	void ReleaseTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    // ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

    // ÃÑ¾Ë
    UPROPERTY(Transient)
    UNDObjectPoolManager* BulletPool;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<ANDBullet> BulletClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    int32 PoolSize = 30;

    // ¹ß»ç
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float FireRate = 0.1f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    bool bAutomatic = true;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    FName MuzzleSocketName = "Muzzle";

    // ÀÌÆåÆ®
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* MuzzleFlash;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    USoundBase* FireSound;


    // Å¸ÀÌ¸Ó
    FTimerHandle FireRateTimerHandle;
    bool bCanFire = true;

private:
    void InitializeBulletPool();
    void StartFiring();
    void StopFiring();
    void Fire();
    FVector GetMuzzleLocation() const;
    FRotator GetMuzzleRotation() const;
};
