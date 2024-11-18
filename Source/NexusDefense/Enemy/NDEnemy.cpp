// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NDEnemy.h"
#include "Manager/NDAIManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/NDPoolableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

ANDEnemy::ANDEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // AI ����
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Ǯ�� ������Ʈ �߰�
    PoolableComponent = CreateDefaultSubobject<UNDPoolableComponent>(TEXT("PoolableComponent"));

    // �̵� ����
    GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

    HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));

    // ������ �̺�Ʈ ���ε�
    if (HealthComponent)
    {
        HealthComponent->OnDamageEvent.AddUObject(this, &ANDEnemy::OnDamageReceived);
    }
}

void ANDEnemy::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

    // AI ��Ʈ�ѷ� Ȯ��
    if (!GetController()->IsA(AAIController::StaticClass()))
    {
        SpawnDefaultController();
    }
}

void ANDEnemy::OnDamageReceived(const FND_S_DamageInfo& DamageInfo)
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy took damage: %f"), DamageInfo.Amount);
}

void ANDEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // AI ������Ʈ ��û
    if (UNDAIManager* AIManager = GetGameInstance()->GetSubsystem<UNDAIManager>())
    {
        AIManager->RequestAIUpdate(this);
    }
}

void ANDEnemy::ExecuteAIResult(const FNDAITask& CompletedTask)
{
    // AI ����� ���� �ൿ ����
    if (CompletedTask.bInAttackRange)
    {
        // ���� ���� �ȿ� ���� ��
        UE_LOG(LogTemp, Display, TEXT("%s is in attack range"), *GetName());
        // ���⿡ ���� ���� �߰� ����
    }
    else if (CompletedTask.bShouldMove)
    {
        // �̵��ؾ� �� ��
        UE_LOG(LogTemp, Display, TEXT("%s is moving to target"), *GetName());

        if (AAIController* AIController = Cast<AAIController>(GetController()))
        {
            AIController->MoveToLocation(CompletedTask.TargetLocation);
            UE_LOG(LogTemp, Display, TEXT("%s started moving to: %s"),
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