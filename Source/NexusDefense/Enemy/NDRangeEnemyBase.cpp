// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDRangeEnemyBase.h"
#include "AI/NDAICBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/NDProjectileBase.h"

ANDRangeEnemyBase::ANDRangeEnemyBase()
{
	// 프로젝타일 스폰 포인트 생성
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ANDRangeEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDRangeEnemyBase::PerformAttack()
{

    FireProjectile();
    
}


void ANDRangeEnemyBase::FireProjectile()
{
	if (ProjectileClass && ProjectileSpawnPoint)
	{
		ANDAICBase* AIC = Cast<ANDAICBase>(GetController());

		if (!(AIC && AIC->TargetCharacter))
		{
			UE_LOG(LogTemp, Error, TEXT("No target to fire at"));

			return;
		}
		
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ANDProjectileBase* TempProjectile = GetWorld()->SpawnActor<ANDProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (!TempProjectile)
		{
			UE_LOG(LogTemp, Error, TEXT("Projectile not spawned"));

			return;
		}

		if (UProjectileMovementComponent* ProjectileMovement = TempProjectile->FindComponentByClass<UProjectileMovementComponent>())
		{
			ProjectileMovement->InitialSpeed = ProjectileSpeed;
			ProjectileMovement->MaxSpeed = ProjectileSpeed;
		}
	}
}
