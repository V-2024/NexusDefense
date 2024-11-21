// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacter.h"
#include "Weapon/NDBaseWeapon.h"

ANDCombatCharacter::ANDCombatCharacter()
{
    // 전투 컴포넌트 생성
    CombatComponent = CreateDefaultSubobject<UNDCombatComponent>(TEXT("CombatComponent"));
    AttacksComponent = CreateDefaultSubobject<UNDAttacksComponent>(TEXT("AttacksComponent"));
}

void ANDCombatCharacter::BeginPlay()
{
    Super::BeginPlay();

    EquipWeapon();
}

void ANDCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 전투 입력 바인딩
    PlayerInputComponent->BindAction("BasicAttack", IE_Pressed, this, & ANDCombatCharacter::PressLMB);
    PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard1);
    PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard2);
    PlayerInputComponent->BindAction("Skill3", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard3);
    PlayerInputComponent->BindAction("Skill4", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard4);
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

    // 디버그 로그
    if (bHit && HitResult.GetActor())
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
            FString::Printf(TEXT("Target Found: %s"), *HitResult.GetActor()->GetName()));
    }

    return bHit ? HitResult.GetActor() : nullptr;
}

void ANDCombatCharacter::HandleAttack(FName SkillName)
{
    // 전방의 적 탐지
    if (AActor* Target = FindTargetInFront())
    {
        // 타겟을 향해 회전
        FVector Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Z = 0;
        SetActorRotation(Direction.Rotation());
    }

    // 스킬 실행
    if (CombatComponent)
    {
        CombatComponent->ExecuteSkill(SkillName);
    }
}

void ANDCombatCharacter::ExecuteBasicAttack()
{
    CombatComponent->ProcessComboCommand();
}

void ANDCombatCharacter::PressLMB()
{
    ExecuteBasicAttack();
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