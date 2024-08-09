// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDRangeEnemyBase.h"
#include "AI/NDAICBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/NDProjectileBase.h"
#include "DamageSystem/ND_C_DamageSystem.h"
#include "Data/NDRangeEnemyData.h"
#include "GameFramework/CharacterMovementComponent.h"

ANDRangeEnemyBase::ANDRangeEnemyBase(FString DataPath)
{
	// 프로젝타일 스폰 포인트 생성
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	SetDataPath(DataPath);
}

void ANDRangeEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	LoadEnemyData();
}

void ANDRangeEnemyBase::PerformAttack()
{

    FireProjectile();
	UE_LOG(LogTemp, Warning, TEXT("PerformAttack"));
    
}


void ANDRangeEnemyBase::LoadEnemyData()
{
	DataAssetPath = TEXT("'/Game/NexusDefense/Enemy/NDC_RangeEnemyData.NDC_RangeEnemyData'");
	UE_LOG(LogTemp, Warning, TEXT("DataAssetPath: %s"), *DataAssetPath);
	UNDRangeEnemyData* EnemyData = LoadObject<UNDRangeEnemyData>(nullptr, *DataAssetPath);

	if (EnemyData)
	{
		SpawnEffect = EnemyData->SpawnEffect;
		DestroyEffect = EnemyData->DestroyEffect;
		SpawnSound = EnemyData->SpawnSound;
		DestroySound = EnemyData->DestroySound;
		Name = EnemyData->Name;
		ExperiencePoints = EnemyData->ExperiencePoints;
		SpawnAnimMontage = EnemyData->SpawnAnimMontage;
		DeathAnimMontage = EnemyData->DeathAnimMontage;
		AttackCooldown = EnemyData->AttackCooldown;
		AttackDamage = EnemyData->AttackDamage;
		ProjectileClass = EnemyData->ProjectileClass;
		ProjectileSpeed = EnemyData->ProjectileSpeed;

		GetMesh()->SetSkeletalMesh(EnemyData->Mesh);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(EnemyData->AnimationBlueprint);

		GetCharacterMovement()->MaxWalkSpeed = EnemyData->MaxWalkSpeed;
		AIControllerClass = EnemyData->AIControllerClass;

		AController* OldController = GetController();
		AController* NewController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, GetActorLocation(), GetActorRotation());
		if (OldController)
		{
			OldController->Destroy();
			
			NewController->Possess(this);

			// cast tp ANDAICBase
			ANDAICBase* AIC = Cast<ANDAICBase>(NewController);

			AIC->PursuitRadius = EnemyData->PursuitRadius;
			AIC->AttackRadius = EnemyData->AttackRadius;
		}
		

		// print EnemyDataAsset.Object->Mesh Path
		UE_LOG(LogTemp, Warning, TEXT("Mesh Path: %s"), *EnemyData->Mesh->GetPathName());

		UE_LOG(LogTemp, Warning, TEXT("Data Asset found"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Data Asset not found"));
	}
}

void ANDRangeEnemyBase::SetDataPath(FString DataPath)
{
	DataAssetPath = DataPath;
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
