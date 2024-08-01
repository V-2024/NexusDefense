// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/NDNexus.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANDNexus::ANDNexus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NexusBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NexusBase"));
	NexusLazer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NexusLazer"));

	RootComponent = NexusBase;
	NexusLazer->SetupAttachment(NexusBase);
	NexusLazer->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NexusBaseMeshRef(TEXT("/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder"));
	if (NexusBaseMeshRef.Object)
	{
		NexusBase->SetStaticMesh(NexusBaseMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NexusLazerMeshRef(TEXT("/Game/LevelPrototyping/Meshes/SM_Ramp.SM_Ramp"));
	if (NexusLazerMeshRef.Object)
	{
		NexusLazer->SetStaticMesh(NexusLazerMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void ANDNexus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDNexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

