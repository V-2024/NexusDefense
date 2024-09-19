// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/NDBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ANDBullet::ANDBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	collisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComponent->SetSphereRadius(10);
	RootComponent = collisionComponent;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetupAttachment(collisionComponent);
	meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComponent->SetRelativeScale3D(FVector(0.25f));
	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	movementComponent->SetUpdatedComponent(collisionComponent);
	
	movementComponent->InitialSpeed = 5000;
	movementComponent->MaxSpeed = 5000;
	movementComponent->bShouldBounce = true;
	movementComponent->Bounciness = 0.5f;
	movementComponent->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ANDBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

