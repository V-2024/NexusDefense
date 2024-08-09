#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANDEnemyBase::ANDEnemyBase()
{
    PrimaryActorTick.bCanEverTick = false;

}

void ANDEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	PlaySpawnEffect();
    PlaySpawnSound();
    PlaySpawnAnimMontage();

    FVector NewLocation = GetMesh()->GetRelativeLocation();
    NewLocation.Z -= 90.0f;  // Z축으로 -100 이동
    GetMesh()->SetRelativeLocation(NewLocation);
}

void ANDEnemyBase::Destroyed()
{
    Super::Destroyed();
    PlayDestroyEffect();
    PlayDestroySound();
    PlayDeathAnimMontage();
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

void ANDEnemyBase::PlaySpawnSound()
{
    if (SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
	}
}

void ANDEnemyBase::PlayDestroySound()
{
	if (DestroySound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
	}
}

void ANDEnemyBase::PlaySpawnAnimMontage()
{
	if (SpawnAnimMontage)
	{
		PlayAnimMontage(SpawnAnimMontage);
	}
}

void ANDEnemyBase::PlayDeathAnimMontage()
{
	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
	}
}




