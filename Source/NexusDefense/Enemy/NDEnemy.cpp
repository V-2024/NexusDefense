// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDEnemy.h"
#include "Manager/NDAIManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pattern/NDPoolableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

ANDEnemy::ANDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // AI 설정
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // 풀링 컴포넌트 추가
    PoolableComponent = CreateDefaultSubobject<UNDPoolableComponent>(TEXT("PoolableComponent"));

    // 이동 설정
    GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void ANDEnemy::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

    // AI 컨트롤러 확인
    if (!GetController()->IsA(AAIController::StaticClass()))
    {
        SpawnDefaultController();
    }
}

void ANDEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // AI 업데이트 요청
    if (UNDAIManager* AIManager = GetGameInstance()->GetSubsystem<UNDAIManager>())
    {
        AIManager->RequestAIUpdate(this);
    }
}

void ANDEnemy::ExecuteAIResult(const FNDAITask& CompletedTask)
{
    // AI 결과에 따른 행동 실행
    if (CompletedTask.bInAttackRange)
    {
        // 공격 범위 안에 있을 때
        UE_LOG(LogTemp, Warning, TEXT("%s is in attack range"), *GetName());
        // 여기에 공격 로직 추가 예정
    }
    else if (CompletedTask.bShouldMove)
    {
        // 이동해야 할 때
        UE_LOG(LogTemp, Warning, TEXT("%s is moving to target"), *GetName());

        if (AAIController* AIController = Cast<AAIController>(GetController()))
        {
            AIController->MoveToLocation(CompletedTask.TargetLocation);
            UE_LOG(LogTemp, Warning, TEXT("%s started moving to: %s"),
                *GetName(),
                *CompletedTask.TargetLocation.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("%s has no AI Controller"), *GetName());
        }
    }
}

void ANDEnemy::ActivateEnemy(const FVector& SpawnLocation)
{
    SetActorLocation(SpawnLocation);
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->GetPathFollowingComponent()->Cleanup();
    }

    if (PoolableComponent)
    {
        PoolableComponent->ActivatePoolable();
    }
}

void ANDEnemy::DeactivateEnemy()
{
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->StopMovement();
    }

    if (PoolableComponent)
    {
        PoolableComponent->DeactivatePoolable();
    }
}