// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/NDNormalEnemyBase.h"
#include "NDRangeEnemyBase.generated.h"

class ANDProjectileBase;


UCLASS()
class NEXUSDEFENSE_API ANDRangeEnemyBase : public ANDNormalEnemyBase
{
	GENERATED_BODY()
	
public:
    ANDRangeEnemyBase() {};
    ANDRangeEnemyBase(FString);
    void LoadEnemyData();
    void SetDataPath(FString);

protected:
	virtual void BeginPlay() override;
	virtual void PerformAttack() override;
    virtual void FireProjectile();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Range Enemy")
    TSubclassOf<ANDProjectileBase> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Range Enemy")
    float ProjectileSpeed;

    UPROPERTY(VisibleAnywhere, Category = "Range Enemy")
    USceneComponent* ProjectileSpawnPoint;

private:
    FString DataAssetPath;
};
