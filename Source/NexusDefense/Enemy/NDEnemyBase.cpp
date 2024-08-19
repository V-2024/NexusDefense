#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANDEnemyBase::ANDEnemyBase()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsActive = false;
}

void ANDEnemyBase::BeginPlay()
{
	Super::BeginPlay();
    /*
	PlaySpawnEffect();
    PlaySpawnSound();
    PlaySpawnAnimMontage();

    FVector NewLocation = GetMesh()->GetRelativeLocation();
    NewLocation.Z -= 90.0f;  // Z축으로 -100 이동
    GetMesh()->SetRelativeLocation(NewLocation);
    */
}

void ANDEnemyBase::Destroyed()
{
    Super::Destroyed();

    /*
    PlayDestroyEffect();
    PlayDestroySound();
    PlayDeathAnimMontage();
    */
}

void ANDEnemyBase::Activate()
{
    if(!bIsActive)
    {
        bIsActive = true;
        SetActorHiddenInGame(false);
        SetActorEnableCollision(true);
        SetActorTickEnabled(true);

        PlaySpawnEffect();
        PlaySpawnSound();
        PlaySpawnAnimMontage();

        FVector NewLocation = GetMesh()->GetRelativeLocation();
        NewLocation.Z -= 90.0f;
        GetMesh()->SetRelativeLocation(NewLocation);

        // 추가적인 초기화 로직을 여기에 구현합니다.
    }
}

void ANDEnemyBase::Deactivate()
{
    if (bIsActive)
    {
        bIsActive = false;
        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);
        SetActorTickEnabled(false);

        PlayDestroyEffect();
        PlayDestroySound();
        PlayDeathAnimMontage();

        OnEnemyDestroyed.Broadcast(this);
    }
}

void ANDEnemyBase::Reset()
{
    // 적의 상태를 초기 상태로 리셋합니다.
    // HP, 위치, 기타 상태 변수들을 초기화합니다.
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




