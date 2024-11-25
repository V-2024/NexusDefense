// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacter.h"
#include "Weapon/NDBaseWeapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

ANDCombatCharacter::ANDCombatCharacter()
{
    // 전투 컴포넌트 생성
    CombatComponent = CreateDefaultSubobject<UNDCombatComponent>(TEXT("CombatComponent"));
    AttackComponent = CreateDefaultSubobject<UNDAttacksComponent>(TEXT("AttackComponent"));
    SkillComponent = CreateDefaultSubobject<UNDSkillComponent>(TEXT("SkillComponent"));
}

void ANDCombatCharacter::BeginPlay()
{
    Super::BeginPlay();
    EquipWeapon();
}

void ANDCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("BasicAttack", IE_Pressed, this, &ANDCombatCharacter::PressLMB);
    PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard1);
    PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard2);
    PlayerInputComponent->BindAction("Skill3", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard3);
    PlayerInputComponent->BindAction("Skill4", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard4);
}

void ANDCombatCharacter::HandleAttack(FName SkillName)
{
    if (AActor* Target = FindTargetInFront())
    {
        FVector Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Z = 0;
        SetActorRotation(Direction.Rotation());
    }

    if (SkillComponent)
    {
        SkillComponent->ExecuteSkill(SkillName);
    }
}

AActor* ANDCombatCharacter::FindTargetInFront()
{
    FVector Start = GetActorLocation();
    FVector End = Start + (GetActorForwardVector() * AttackTraceDistance);

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    FHitResult HitResult;
    bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
        GetWorld(),
        Start,
        End,
        AttackTraceRadius,
        ObjectTypes,
        false,
        TArray<AActor*>{this},
        EDrawDebugTrace::ForDuration,
        HitResult,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        2.0f
    );

    return bHit ? HitResult.GetActor() : nullptr;
}

void ANDCombatCharacter::EquipWeapon()
{
    if (WeaponClass)
    {
        Weapon = GetWorld()->SpawnActor<ANDBaseWeapon>(WeaponClass);
        if (Weapon)
        {
            Weapon->AttachToComponent(GetMesh(),
                FAttachmentTransformRules::KeepRelativeTransform,
                TEXT("WeaponSocket"));
            Weapon->SetOwner(this);
        }
    }
}

void ANDCombatCharacter::PressLMB()
{
    ExecuteBasicAttack();
}

void ANDCombatCharacter::ExecuteBasicAttack()
{
    if (AActor* Target = FindTargetInFront())
    {
        FVector Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Z = 0;
        SetActorRotation(Direction.Rotation());

        if (AttackComponent)
        {
            FND_S_AttackInfo AttackInfo;
            AttackInfo.Damage = 10.0f; // 기본 공격 데미지
            AttackComponent->ExecuteAttack(EAttackTraceType::SphereTrace, AttackInfo, AttackTraceRadius, AttackTraceDistance);
        }
    }
}

void ANDCombatCharacter::PressKeyboard1()
{
    HandleAttack(FName("SkillA"));
}

void ANDCombatCharacter::PressKeyboard2()
{
    HandleAttack(FName("SkillB"));
}

void ANDCombatCharacter::PressKeyboard3()
{
    HandleAttack(FName("SkillC"));
}

void ANDCombatCharacter::PressKeyboard4()
{
    HandleAttack(FName("SkillD"));
}

void ANDCombatCharacter::MoveForward(float Value)
{
    if (CombatComponent && CombatComponent->GetCurrentState() == ECombatState::Attacking)
    {
        return;
    }

    Super::MoveForward(Value);
}

void ANDCombatCharacter::MoveRight(float Value)
{
    if (CombatComponent && CombatComponent->GetCurrentState() == ECombatState::Attacking)
    {
        return;
    }

    Super::MoveRight(Value);
}