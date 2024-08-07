// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDNormalEnemyBase.h"
#include "AI/NDAICBase.h"

ANDNormalEnemyBase::ANDNormalEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDNormalEnemyBase::BeginPlay()
{
	Super::BeginPlay();

    AIController = Cast<ANDAICBase>(GetController());
}

void ANDNormalEnemyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ANDNormalEnemyBase::PursuitPlayer()
{

}

void ANDNormalEnemyBase::AttackPlayer()
{
    float CurrentTime = GetWorld()->GetTimeSeconds();

    if (CurrentTime - LastAttackTime >= AttackCooldown)
    {
        LastAttackTime = CurrentTime;

        PerformAttack();
    }
}

void ANDNormalEnemyBase::PerformAttack()
{

}


