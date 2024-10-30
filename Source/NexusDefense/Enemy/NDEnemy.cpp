// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDEnemy.h"
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

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

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

	ChasePlayer();
}

void ANDEnemy::ChasePlayer()
{
	if (!PlayerCharacter || !IsPlayerInRange())
		return;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
		return;

	AIController->MoveToActor(PlayerCharacter, -1.0f, true, true, true);
}

bool ANDEnemy::IsPlayerInRange() const
{
	if (!PlayerCharacter)
		return false;

	float DistanceToPlayer = FVector::Distance(
		GetActorLocation(),
		PlayerCharacter->GetActorLocation()
	);

	return DistanceToPlayer <= DetectionRange;
}

