// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NDEnemyBase.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	ANDEnemyBase();

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

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlaySpawnEffect();

    UFUNCTION(BlueprintCallable, Category = "Enemy Actions")
    void PlayDestroyEffect();
};
