// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacter.h"
#include "Weapon/NDBaseWeapon.h"

ANDCombatCharacter::ANDCombatCharacter()
{
    // ���� ������Ʈ ����
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

    // ���� �Է� ���ε�
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

    // ����� �α�
    if (bHit && HitResult.GetActor())
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
            FString::Printf(TEXT("Target Found: %s"), *HitResult.GetActor()->GetName()));
    }

    return bHit ? HitResult.GetActor() : nullptr;
}

void ANDCombatCharacter::HandleAttack(FName SkillName)
{
    // ������ �� Ž��
    if (AActor* Target = FindTargetInFront())
    {
        // Ÿ���� ���� ȸ��
        FVector Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Z = 0;
        SetActorRotation(Direction.Rotation());
    }

    // ��ų ����
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