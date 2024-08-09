// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "NDEnemyBase.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANDEnemyBase();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlaySpawnEffect();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlayDestroyEffect();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlaySpawnSound();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlayDestroySound();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlaySpawnAnimMontage();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlayDeathAnimMontage();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:	
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* SpawnAnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* DeathAnimMontage;
};
