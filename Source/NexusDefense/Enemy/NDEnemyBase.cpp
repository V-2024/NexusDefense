#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANDEnemyBase::ANDEnemyBase()
{
	Name = TEXT("Default Enemy");
	ExperiencePoints = 10;
}

void ANDEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	PlaySpawnEffect();
}

void ANDEnemyBase::Destroyed()
{

}


void ANDEnemyBase::PlaySpawnEffect()
{
    if (SpawnEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEffect, GetActorLocation());
    }
    if (SpawnSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
    }
}

void ANDEnemyBase::PlayDestroyEffect()
{
    if (DestroyEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation());
    }
    if (DestroySound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
    }
}
