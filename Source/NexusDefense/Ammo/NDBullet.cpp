// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/NDBullet.h"
#include "Manager/NDObjectPoolManager.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ANDBullet::ANDBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoolableComponent = CreateDefaultSubobject<UNDPoolableComponent>(TEXT("PoolableComponent"));

	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	collisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	collisionComponent->SetSphereRadius(10);
	collisionComponent->OnComponentHit.AddDynamic(this, &ANDBullet::OnHit);
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

	InitializeComponents();

	//PoolableComponent->OnPoolableActivated.AddLambda([this]()
	//	{
	//		movementComponent->Velocity = FVector::ZeroVector;
	//		movementComponent->SetActive(true);
	//	});

	//PoolableComponent->OnPoolableDeactivated.AddLambda([this]()
	//	{
	//		movementComponent->SetActive(false);
	//	});
}

// Called when the game starts or when spawned
void ANDBullet::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("collision Profile: %s"), *collisionComponent->GetCollisionProfileName().ToString());
}

void ANDBullet::FireInDirection(const FVector& Direction)
{
	if (movementComponent)
	{
		movementComponent->Velocity = Direction * movementComponent->InitialSpeed;
	}

	GetWorld()->GetTimerManager().SetTimer(
		LifeSpanTimer,
		[this]()
		{
			if (PoolableComponent)
			{
				PoolableComponent->ReturnToPool();
			}
		},
		LifeSpan,
		false
	);

}

void ANDBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 데미지 적용 관련 함수 추가해야함.
		PoolableComponent->ReturnToPool();
}

// Called every frame
void ANDBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ANDBullet::InitializeComponents()
{
	if (collisionComponent)
	{
		collisionComponent->OnComponentHit.AddDynamic(this, &ANDBullet::OnHit);
	}
}