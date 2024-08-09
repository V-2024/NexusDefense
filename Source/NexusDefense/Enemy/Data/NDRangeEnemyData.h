// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Projectile/NDProjectileBase.h"
#include "AIController.h"
#include "NDRangeEnemyData.generated.h"

/**
 * 
 */
UCLASS()
class NEXUSDEFENSE_API UNDRangeEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UNDRangeEnemyData();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    USkeletalMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSubclassOf<UAnimBlueprint> AnimationBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* SpawnAnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* SpawnEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UParticleSystem* DestroyEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
    USoundBase* SpawnSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
    USoundBase* DestroySound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    int32 ExperiencePoints;
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range Attack")
    float AttackCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range Attack")
    float AttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    TSubclassOf<ANDProjectileBase> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float PursuitRadius;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float AttackRadius;
};
