// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDSoundManager.generated.h"

class UNDObjectPoolManager;
class UAudioComponent;

UCLASS()
class NEXUSDEFENSE_API UNDSoundManager : public UObject
{
	GENERATED_BODY()

public:
    UNDSoundManager();

    void Initialize(UNDObjectPoolManager* PoolManager);

    UFUNCTION(BlueprintCallable, Category = "Sound")
    void PlaySound(USoundBase* Sound, const FVector& Location, float VolumeMultiplier = 1.0f, float PitchMultiplier = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Sound")
    void StopSound(UAudioComponent* AudioComponent);

    UFUNCTION(BlueprintCallable, Category = "Music")
    void PlayBackgroundMusic(USoundBase* Music);

    UFUNCTION(BlueprintCallable, Category = "Music")
    void StopBackgroundMusic();

private:
    UPROPERTY()
    UNDObjectPoolManager* ObjectPoolManager;

    UPROPERTY()
    TArray<UAudioComponent*> ActiveSounds;

    UPROPERTY()
    UAudioComponent* BackgroundMusicComponent;

    void UpdateActiveSounds(float DeltaTime);
};
