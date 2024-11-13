// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NDAttacksComponent.h"

// Sets default values for this component's properties
UNDAttacksComponent::UNDAttacksComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UNDAttacksComponent::PerformMeleeAttack()
{
    AActor* Owner = GetOwner();
    if (!Owner) return false;

    UE_LOG(LogTemp, Log, TEXT("%s is performing attack!"), *Owner->GetName());
    UE_LOG(LogTemp, Log, TEXT("Attack Details - Damage: %.2f, Type: %d"), DamageAmount, (int32)DamageType);

    FS_DamageInfo DamageInfo;
    DamageInfo.Amount = DamageAmount;
    DamageInfo.DamageType = DamageType;
    DamageInfo.DamageResponse = DamageResponse;
    DamageInfo.CanBeBlocked = true;
    DamageInfo.ShouldForceInterrupt = true;

    UE_LOG(LogTemp, Log, TEXT("Attack Info - DamageType: %d, Response: %d"),
        (int32)DamageInfo.DamageType,
        (int32)DamageInfo.DamageResponse);

    return true;
}

void UNDAttacksComponent::ActivateAttack()
{
    if (AttackCollision)
    {
        AlreadyHitActors.Empty();
        AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        UE_LOG(LogTemp, Log, TEXT("Attack Collision Activated"));
    }
}

void UNDAttacksComponent::DeactivateAttack()
{
    if (AttackCollision)
    {
        AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        UE_LOG(LogTemp, Log, TEXT("Attack Collision Deactivated"));
    }
}


// Called when the game starts
void UNDAttacksComponent::BeginPlay()
{
	Super::BeginPlay();
    InitializeCollision();
}


void UNDAttacksComponent::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == GetOwner()) return;
\
    if (AlreadyHitActors.Contains(OtherActor)) return;

    // 데미지 적용
    if (INDDamageableInterface* DamageableActor = Cast<INDDamageableInterface>(OtherActor))
    {
        FS_DamageInfo DamageInfo;
        DamageInfo.Amount = DamageAmount;
        DamageInfo.DamageType = DamageType;
        DamageInfo.DamageResponse = DamageResponse;
        DamageInfo.CanBeBlocked = true;
        DamageInfo.ShouldForceInterrupt = true;

        if (DamageableActor->TakeDamage(DamageInfo))
        {
            // 성공적으로 데미지를 입혔다면 히트 목록에 추가
            AlreadyHitActors.Add(OtherActor);
            UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *OtherActor->GetName());
        }
    }
}

// Called every frame
void UNDAttacksComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNDAttacksComponent::InitializeCollision()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // 스피어 콜리전 생성
    AttackCollision = NewObject<USphereComponent>(OwnerCharacter, TEXT("AttackCollision"));
    AttackCollision->SetupAttachment(OwnerCharacter->GetMesh(), WeaponSocketName);
    AttackCollision->SetSphereRadius(20.0f);
    AttackCollision->SetCollisionProfileName(TEXT("OverlapAll"));
    AttackCollision->SetGenerateOverlapEvents(true);
    AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &UNDAttacksComponent::OnAttackOverlapBegin);

    AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AttackCollision->RegisterComponent();
}

