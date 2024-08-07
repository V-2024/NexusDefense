// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NDAICBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Enemy/NDNormalEnemyBase.h"

ANDAICBase::ANDAICBase()
{
    ClosestDistance = MAX_FLT;
}

void ANDAICBase::BeginPlay()
{
    Super::BeginPlay();
}

// 현재 상태 검사 및 해당 상태
void ANDAICBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateEnemyState();
    UpdateTargetCharacter();

    switch (CurrentState)
    {
    case EEnemyState::Pursuit:
        PursuitPlayer();
        break;
    case EEnemyState::Attack:
        AttackPlayer();
        break;
    default:
        break;
    }
}

void ANDAICBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

}

void ANDAICBase::UpdateEnemyState()
{
	if (TargetCharacter == nullptr)
	{
		return;
	}

	float Distance = GetPawn()->GetDistanceTo(TargetCharacter);

	if (Distance < AttackRadius)
	{
		CurrentState = EEnemyState::Attack;
	}
	else
	{
		CurrentState = EEnemyState::Pursuit;
	}
}

void ANDAICBase::PursuitPlayer()
{
    if (TargetCharacter)
    {
        MoveToActor(TargetCharacter, AttackRadius - 10.0f);
    }
}

void ANDAICBase::AttackPlayer()
{
    ANDNormalEnemyBase* Enemy = Cast<ANDNormalEnemyBase>(GetPawn());
	if (Enemy)
	{
        Enemy->AttackPlayer();
	}
}

void ANDAICBase::FindPlayerCharacters()
{
	TArray<AActor*> PlayerActors;

    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), PlayerActors);

    if (PlayerActors.IsEmpty())
	{
        UE_LOG(LogTemp, Warning, TEXT("Can Not Found Player Character"));

        return;
	}

	for (AActor* Player : PlayerActors)
	{
		if (ACharacter* PlayerCharacter = Cast<ACharacter>(Player))
		{
			PlayerCharacters.Add(PlayerCharacter);
		}
	}
}

void ANDAICBase::UpdateTargetCharacter()
{
    if (PlayerCharacters.Num() == 0)
	{
        UE_LOG(LogTemp, Warning, TEXT("Can Not Update Player Character "));
        
		return;
	}


    for (ACharacter* Player : PlayerCharacters)
	{
		float Distance = GetPawn()->GetDistanceTo(Player);

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestCharacter = Player;
		}
	}

	TargetCharacter = ClosestCharacter;
}
