// Fill out your copyright notice in the Description page of Project Settings.


#include "Drops/NDItemBase.h"


// Sets default values
ANDItemBase::ANDItemBase()
{
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    RootComponent = CollisionSphere;
    CollisionSphere->SetSphereRadius(50.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // 메시 생성
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    ItemMesh->SetupAttachment(CollisionSphere);
    ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANDItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

