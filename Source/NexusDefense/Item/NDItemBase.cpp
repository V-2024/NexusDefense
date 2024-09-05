// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/NDItemBase.h"
#include "Manager/NDItemManager.h"

// Sets default values
ANDItemBase::ANDItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->SetCollisionProfileName("OverlapAllDynamic");

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANDItemBase::OnOverlapBegin);

}

void ANDItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ANDCharacterBase* Character = Cast<ANDCharacterBase>(OtherActor))
    {
        if (ItemManager)
        {
            ItemManager->ProcessItemEffect(this, Character);
        }
        else
        {
            ApplyEffectToCharacter(Character);
            Destroy();
        }
    }
}

void ANDItemBase::ApplyEffectToCharacter(ANDCharacterBase* Character)
{

}

// Called when the game starts or when spawned
void ANDItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

