// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDBullet.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDBullet();

	void FireInDirection(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* movementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* collisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "BodyMesh")
	class UStaticMeshComponent* meshComponent;

};
