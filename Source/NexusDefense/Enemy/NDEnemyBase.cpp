// NDEnemyBase.cpp
#include "Enemy/NDEnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIBase/NDWidgetComponent.h"
#include "UI/Combat/NDHPBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/NDEventManager.h"
#include "GameInstance/NDGameInstance.h"

ANDEnemyBase::ANDEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.SetTickFunctionEnable(false);
    
    bIsActive = false;
    CurrentState = EEnemyState::Inactive;
    
    SetupComponents();
}

void ANDEnemyBase::BeginPlay()
{
    Super::BeginPlay();
    
    // Get EventManager from GameInstance
    if (UNDGameInstance* GameInstance = Cast<UNDGameInstance>(GetGameInstance()))
    {
        EventManager = GameInstance->GetEventManager();
    }
    
    // Setup Health Component Delegates
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddDynamic(this, &ANDEnemyBase::OnHealthChanged);
        HealthComponent->OnDamageEvent.AddUObject(this, &ANDEnemyBase::OnDamageTaken);
        HealthComponent->OnDeathEvent.AddUObject(this, &ANDEnemyBase::OnDeathTriggered);
    }
}

void ANDEnemyBase::SetupComponents()
{
    // Health Component
    HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));
    
    // HP Bar Widget
    HPBar = CreateDefaultSubobject<UNDWidgetComponent>(TEXT("HPBar"));
    HPBar->SetupAttachment(GetMesh());
    HPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
    
    static ConstructorHelpers::FClassFinder<UUserWidget> HPBarWidgetClassRef(TEXT("/Game/NexusDefense/UI/Combat/WBP_HPBar.WBP_HPBar_C"));
    if (HPBarWidgetClassRef.Class)
    {
        HPBar->SetWidgetClass(HPBarWidgetClassRef.Class);
        HPBar->SetWidgetSpace(EWidgetSpace::Screen);
        HPBar->SetDrawSize(FVector2D(200.0f, 15.0f));
        HPBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ANDEnemyBase::OnHealthChanged(float NewHealth, float Delta)
{
    // Update HP Bar
    if (UNDHPBarWidget* HPBarWidget = Cast<UNDHPBarWidget>(HPBar->GetWidget()))
    {
        HPBarWidget->UpdateHPBar(NewHealth);
    }
    
    // Broadcast via EventManager if needed
    if (Delta < 0 && EventManager)
    {
        // You might want to broadcast damage taken event
        EventManager->TriggerEnemyDamageTaken(this, -Delta);
    }
}

void ANDEnemyBase::OnDamageTaken(const FND_S_DamageInfo& DamageInfo)
{
    OnHit();
    
    if (EventManager)
    {
        // Broadcast damage event through EventManager if needed
        EventManager->TriggerEnemyDamageReceived(this, DamageInfo);
    }
}

void ANDEnemyBase::OnDeathTriggered()
{
    SetEnemyState(EEnemyState::Dying);
    OnDeath();
    
    if (EventManager)
    {
        EventManager->TriggerEnemyDefeated(this);
    }
}

void ANDEnemyBase::ApplyStun(float Duration)
{
    if (!CanBeStunned() || CurrentState == EEnemyState::Dying || CurrentState == EEnemyState::Inactive)
        return;

    SetEnemyState(EEnemyState::Stunned);
    
    // Clear existing timer if any
    if (GetWorld()->GetTimerManager().IsTimerActive(StunTimerHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
    }
    
    // Set timer to exit stun
    GetWorld()->GetTimerManager().SetTimer(
        StunTimerHandle,
        [this]()
        {
            if (CurrentState == EEnemyState::Stunned)
            {
                SetEnemyState(EEnemyState::Active);
            }
        },
        Duration,
        false
    );
}

void ANDEnemyBase::OnSpawn()
{
    SetEnemyState(EEnemyState::Spawning);
    PlayStateEffects(EEnemyState::Spawning);
    
    if (EventManager)
    {
        EventManager->TriggerEnemySpawned(this);
    }
    
    // Transition to Active state after spawn animation
    FTimerHandle SpawnTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        SpawnTimerHandle,
        [this]()
        {
            SetEnemyState(EEnemyState::Active);
        },
        1.0f, // Adjust based on spawn animation length
        false
    );
}

void ANDEnemyBase::OnDeath()
{
    if (EventManager)
    {
        // Additional death events can be triggered here if needed
    }
    
    // Deactivate after death animation
    FTimerHandle DeathTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        DeathTimerHandle,
        [this]()
        {
            Deactivate();
        },
        2.0f, // Adjust based on death animation length
        false
    );
}

void ANDEnemyBase::OnHit()
{
    // Implement hit reaction
    // Could include visual effects, sounds, or animation
}

void ANDEnemyBase::SetEnemyState(EEnemyState NewState)
{
    if (CurrentState != NewState)
    {
        EEnemyState OldState = CurrentState;
        CurrentState = NewState;
        PlayStateEffects(CurrentState);
        
        // Additional state change logic can be added here
    }
}

void ANDEnemyBase::Activate()
{
    if (!bIsActive)
    {
        bIsActive = true;
        SetActorHiddenInGame(false);
        SetActorEnableCollision(true);
        PrimaryActorTick.SetTickFunctionEnable(true);
        
        if (HealthComponent)
        {
            // Reset health to max
            HealthComponent->AddHealth(HealthComponent->GetMaxHealth());
        }
        
        OnSpawn();
    }
}

void ANDEnemyBase::Deactivate()
{
    if (bIsActive)
    {
        bIsActive = false;
        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);
        PrimaryActorTick.SetTickFunctionEnable(false);
        
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
        HPBar->SetHiddenInGame(true);
        
        SetEnemyState(EEnemyState::Inactive);
    }
}

void ANDEnemyBase::PlayStateEffects(EEnemyState NewState)
{
    switch (NewState)
    {
        case EEnemyState::Spawning:
            PlaySpawnEffect();
            PlaySpawnSound();
            PlaySpawnAnimMontage();
            break;
            
        case EEnemyState::Dying:
            PlayDestroyEffect();
            PlayDestroySound();
            PlayDeathAnimMontage();
            break;
    }
}

// VFX & SFX functions remain the same as your original implementation
void ANDEnemyBase::PlaySpawnEffect() const
{
    if (SpawnEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEffect, GetActorLocation());
    }
}

void ANDEnemyBase::PlayDestroyEffect() const
{
    if (DestroyEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation());
    }
}

void ANDEnemyBase::PlaySpawnSound() const
{
    if (SpawnSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
    }
}

void ANDEnemyBase::PlayDestroySound() const
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

void ANDEnemyBase::SetUpEnemyWidget(UNDUserWidget* Widget)
{
    UNDHPBarWidget* HPBarWidget = Cast<UNDHPBarWidget>(Widget);
    if (HPBarWidget && HealthComponent)
    {
        HPBarWidget->SetMaxHP(HealthComponent->GetMaxHealth());
        HPBarWidget->UpdateHPBar(HealthComponent->GetHealth());
    }
}

void ANDEnemyBase::Destroyed()
{
    Super::Destroyed();
    PlayDestroyEffect();
    PlayDestroySound();
}