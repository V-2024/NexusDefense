#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANDEnemyBase::ANDEnemyBase()
{

}

void ANDEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	PlaySpawnEffect();
    PlaySpawnAnimation();
}

void ANDEnemyBase::Destroyed()
{
    Super::Destroyed();
    PlayDestroyEffect();
    PlayDeathAnimation();
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

void ANDEnemyBase::PlaySpawnAnimation()
{
    if (MeshComponent && SpawnAnimMontage)
	{
		MeshComponent->PlayAnimation(SpawnAnimMontage, false);
	}
}

void ANDEnemyBase::PlayDeathAnimation()
{
    if(MeshComponent && DeathAnimMontage)
    {
		MeshComponent->PlayAnimation(DeathAnimMontage, false);
	}
}
