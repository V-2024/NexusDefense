
#include "Enemy/NDDummyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ANDDummyEnemy::ANDDummyEnemy()
{
    PrimaryActorTick.bCanEverTick = false;

    // 캡슐 컴포넌트 설정
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

    // 메시 설정
    if (USkeletalMeshComponent* MeshComponent = GetMesh())
    {
        MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
        MeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    }

    // Health Component 설정
    HealthComponent = CreateDefaultSubobject<UNDHealthComponent>(TEXT("HealthComponent"));

    // Health Bar Widget Component 설정
    HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
    HealthBarWidget->SetupAttachment(RootComponent);
    HealthBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
    HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
    HealthBarWidget->SetDrawSize(FVector2D(150.0f, 15.0f));
}

void ANDDummyEnemy::BeginPlay()
{
    Super::BeginPlay();

    // 이벤트 바인딩
    if (HealthComponent)
    {
        HealthComponent->OnDamageEvent.AddUObject(this, &ANDDummyEnemy::OnDamageReceived);
        HealthComponent->OnDeathEvent.AddUObject(this, &ANDDummyEnemy::OnDeath);
    }

    // Widget Class 설정
    if (HealthBarWidgetClass)
    {
        HealthBarWidget->SetWidgetClass(HealthBarWidgetClass);
    }
}

void ANDDummyEnemy::OnDamageReceived(const FND_S_DamageInfo& DamageInfo)
{
    PlayHitEffects();
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,
        FString::Printf(TEXT("Dummy took damage: %.1f"), DamageInfo.Amount));
}

void ANDDummyEnemy::OnDeath()
{
    PlayDeathEffects();
    SetActorEnableCollision(false);
    GetMesh()->SetVisibility(false);

    FTimerHandle DestroyTimer;
    GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [this]()
        {
            Destroy();
        }, 3.0f, false);
}

void ANDDummyEnemy::PlayHitEffects()
{
    if (HitEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            HitEffect,
            GetActorLocation(),
            GetActorRotation()
        );
    }

    if (HitSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            HitSound,
            GetActorLocation()
        );
    }
}

void ANDDummyEnemy::PlayDeathEffects()
{
    if (DeathEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            DeathEffect,
            GetActorLocation(),
            GetActorRotation()
        );
    }

    if (DeathSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            DeathSound,
            GetActorLocation()
        );
    }
}