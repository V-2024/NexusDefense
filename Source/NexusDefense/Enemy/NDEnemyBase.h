// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDEnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestroyedSignature, ANDEnemyBase*, DestroyedEnemy);

UCLASS()
class NEXUSDEFENSE_API ANDEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANDEnemyBase();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    virtual void Activate();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    virtual void Deactivate();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    virtual void Reset();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    int32 GetScoreValue() const { return ExperiencePoints; }

    void PlaySpawnEffect();

    void PlayDestroyEffect();

    void PlaySpawnSound();

    void PlayDestroySound();

    void PlaySpawnAnimMontage();

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

    UPROPERTY(BlueprintAssignable, Category = "Enemy")
    FOnEnemyDestroyedSignature OnEnemyDestroyed;

private:
    bool bIsActive;
};
