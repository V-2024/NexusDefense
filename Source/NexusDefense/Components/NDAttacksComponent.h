// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DamageSystem/ND_S_DamageInfo.h"
#include "Interfaces/NDDamageableInterface.h"
#include "NDAttacksComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEXUSDEFENSE_API UNDAttacksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNDAttacksComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool PerformMeleeAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ActivateAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DeactivateAttack();

	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;

	// 공격 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Settings")
	float DamageAmount = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Settings")
	E_DamageType DamageType = E_DamageType::Melee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Settings")
	E_DamageResponse DamageResponse = E_DamageResponse::HitReaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Settings")
	FName WeaponSocketName = "WeaponSocket";

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	USphereComponent* AttackCollision;

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void InitializeCollision();
		
};
