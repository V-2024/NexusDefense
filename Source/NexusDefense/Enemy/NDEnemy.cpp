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

}

// Called when the game starts or when spawned
void ANDEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

