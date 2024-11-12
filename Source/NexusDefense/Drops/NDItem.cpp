// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDItem.h"
#include "Components/SphereComponent.h"

// Sets default values
ANDItem::ANDItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
    RootComponent = CollisionVolume;
}

// Called when the game starts or when spawned
void ANDItem::BeginPlay()
{
	Super::BeginPlay();
	
    CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANDItem::OnOverlapBegin);
    CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ANDItem::OnOverlapEnd);
}

// Called every frame
void ANDItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANDItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Item::OnOverlapBegin()"));
}

void ANDItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("Item::OnOverlapEnd()"));
}

