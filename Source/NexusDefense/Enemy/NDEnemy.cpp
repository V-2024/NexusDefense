// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDEnemy.h"
#include "Pattern/NDPoolableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

// Sets default values
ANDEnemy::ANDEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoolableComponent = CreateDefaultSubobject<UNDPoolableComponent>(TEXT("PoolableComponent"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

}

void ANDEnemy::ActivateEnemy(const FVector& SpawnLocation)
{
	SetActorLocation(SpawnLocation);
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->GetPathFollowingComponent()->Cleanup();
	}

	if (PoolableComponent)
	{
		PoolableComponent->ActivatePoolable();
	}
}

void ANDEnemy::DeactivateEnemy()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}

	if (PoolableComponent)
	{
		PoolableComponent->DeactivatePoolable();
	}
}

// Called when the game starts or when spawned
void ANDEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (!GetController()->IsA(AAIController::StaticClass()))
	{
		SpawnDefaultController();
	}
}

// Called every frame
void ANDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PoolableComponent && PoolableComponent->IsPoolableActive())
	{
		ChasePlayer();
	}
}

void ANDEnemy::ChasePlayer()
{
	if (!PlayerCharacter || !IsPlayerInRange())
		return;

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->MoveToActor(PlayerCharacter, -1.0f, true, true, false);
	}
}

bool ANDEnemy::IsPlayerInRange() const
{
	if (!PlayerCharacter)
		return false;

	float DistanceToPlayer = FVector::Distance(GetActorLocation(),
		PlayerCharacter->GetActorLocation());

	return DistanceToPlayer <= DetectionRange;
}

