// NDAICBase.cpp
#include "AI/NDAICBase.h"
#include "Enemy/NDEnemyBase.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

ANDAICBase::ANDAICBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize default values
    PursuitRadius = 1000.0f;
    AttackRadius = 150.0f;
    ClosestDistance = FLT_MAX;
    CurrentBehaviorState = EAIBehaviorState::Idle;
    
    // Setup AI Perception
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
    UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    
    if (SightConfig)
    {
        SightConfig->SightRadius = PursuitRadius;
        SightConfig->LoseSightRadius = PursuitRadius + 500.0f;
        SightConfig->PeripheralVisionAngleDegrees = 360.0f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        
        AIPerceptionComponent->ConfigureSense(*SightConfig);
        AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    }
}

void ANDAICBase::BeginPlay()
{
    Super::BeginPlay();

    // Bind perception update function
    if (AIPerceptionComponent)
    {
        AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANDAICBase::OnPerceptionUpdated);
    }

    // Initial player character search
    FindPlayerCharacters();
}

void ANDAICBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!CanPerformAction())
        return;

    ACharacter* PerceivedCharacter = Cast<ACharacter>(Actor);
    if (PerceivedCharacter && PlayerCharacters.Contains(PerceivedCharacter))
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            // Add to or update in perceived actors
            UpdateTargetCharacter();
        }
        else
        {
            // Remove from perceived actors if lost sight
            if (TargetCharacter == PerceivedCharacter)
            {
                TargetCharacter = nullptr;
                UpdateTargetCharacter();
            }
        }
    }
}

void ANDAICBase::FindPlayerCharacters()
{
    PlayerCharacters.Empty();
    
    TArray<AActor*> AllCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), AllCharacters);
    
    for (AActor* Actor : AllCharacters)
    {
        ACharacter* PlayerCharacter = Cast<ACharacter>(Actor);
        if (PlayerCharacter && PlayerCharacter->IsPlayerControlled())
        {
            PlayerCharacters.Add(PlayerCharacter);
        }
    }
}

void ANDAICBase::UpdateTargetCharacter()
{
    if (PlayerCharacters.Num() == 0)
    {
        FindPlayerCharacters();
        if (PlayerCharacters.Num() == 0)
            return;
    }

    ClosestCharacter = nullptr;
    ClosestDistance = FLT_MAX;
    FVector MyLocation = GetPawn()->GetActorLocation();

    // Find closest player character
    for (ACharacter* PlayerChar : PlayerCharacters)
    {
        if (PlayerChar)
        {
            float Distance = FVector::Distance(MyLocation, PlayerChar->GetActorLocation());
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                ClosestCharacter = PlayerChar;
            }
        }
    }

    TargetCharacter = ClosestCharacter;
    UpdateBehaviorState();
}

void ANDAICBase::PursuitPlayer()
{
    if (!TargetCharacter || !CanPerformAction())
        return;

    // Get navigation system
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (!NavSystem)
        return;

    // Move to target
    FVector TargetLocation = TargetCharacter->GetActorLocation();
    FAIMoveRequest MoveRequest;
    MoveRequest.SetGoalLocation(TargetLocation);
    MoveRequest.SetAcceptanceRadius(AttackRadius);

    FNavPathSharedPtr NavPath;
    MoveTo(MoveRequest, &NavPath);
}

void ANDAICBase::AttackPlayer()
{
    if (!TargetCharacter || !CanPerformAction())
        return;

    // Get controlled enemy
    ANDEnemyBase* ControlledEnemy = GetControlledEnemy();
    if (!ControlledEnemy)
        return;

    // Face target
    FVector Direction = TargetCharacter->GetActorLocation() - ControlledEnemy->GetActorLocation();
    FRotator NewRotation = Direction.Rotation();
    NewRotation.Pitch = 0.0f;
    ControlledEnemy->SetActorRotation(NewRotation);

    // Here you would trigger the enemy's attack
    // This could be implemented in the Enemy class and called here
    // For example: ControlledEnemy->PerformAttack();
}

void ANDAICBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!CanPerformAction())
        return;

    // Update target if none exists
    if (!TargetCharacter)
    {
        UpdateTargetCharacter();
    }

    UpdateBehaviorState();

    // Execute behavior based on current state
    switch (CurrentBehaviorState)
    {
        case EAIBehaviorState::Idle:
            // Implement idle behavior if needed
            break;
            
        case EAIBehaviorState::Pursuit:
            PursuitPlayer();
            break;
            
        case EAIBehaviorState::Attack:
            AttackPlayer();
            break;
    }
}

bool ANDAICBase::CanPerformAction() const
{
    ANDEnemyBase* ControlledEnemy = GetControlledEnemy();
    if (!ControlledEnemy)
        return false;

    EEnemyState EnemyState = ControlledEnemy->GetCurrentState();
    
    return EnemyState == EEnemyState::Active && 
           !ControlledEnemy->IsStunned();
}

ANDEnemyBase* ANDAICBase::GetControlledEnemy() const
{
    return Cast<ANDEnemyBase>(GetPawn());
}

void ANDAICBase::UpdateBehaviorState()
{
    if (!CanPerformAction())
    {
        CurrentBehaviorState = EAIBehaviorState::Idle;
        return;
    }

    if (TargetCharacter)
    {
        float DistanceToTarget = FVector::Distance(GetPawn()->GetActorLocation(), TargetCharacter->GetActorLocation());
        
        if (DistanceToTarget <= AttackRadius)
        {
            CurrentBehaviorState = EAIBehaviorState::Attack;
        }
        else if (DistanceToTarget <= PursuitRadius)
        {
            CurrentBehaviorState = EAIBehaviorState::Pursuit;
        }
        else
        {
            CurrentBehaviorState = EAIBehaviorState::Idle;
        }
    }
    else
    {
        CurrentBehaviorState = EAIBehaviorState::Idle;
    }
}