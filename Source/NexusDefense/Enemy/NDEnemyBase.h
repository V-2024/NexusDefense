// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/UIBase/NDEnemyWidgetInterface.h"
#include "Components/NDHealthComponent.h"
#include "NDEnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestroyedSignature, ANDEnemyBase*, DestroyedEnemy);

UCLASS()
class NEXUSDEFENSE_API ANDEnemyBase : public ACharacter, public INDEnemyWidgetInterface
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

    void SetComponents();
    void PlaySpawnEffect();
    void PlayDestroyEffect();
    void PlaySpawnSound();
    void PlayDestroySound();
    void PlaySpawnAnimMontage();
    void PlayDeathAnimMontage();

    FORCEINLINE void    SetActive(bool IsActive)       {   bIsActive = IsActive;       }
    FORCEINLINE bool    IsActive() const               {   return bIsActive;           }
    FORCEINLINE float   GetScore() const              {   return ExperiencePoints;    }


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


protected:
    virtual void SetUpEnemyWidget(class UNDUserWidget* Widget) override;

private:
    bool bIsActive;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UNDHealthComponent* HealthComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UNDWidgetComponent> HPBar;
};
