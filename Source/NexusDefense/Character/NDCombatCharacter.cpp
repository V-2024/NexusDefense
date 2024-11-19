// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacter.h"

ANDCombatCharacter::ANDCombatCharacter()
{
    // ���� ������Ʈ ����
    CombatComponent = CreateDefaultSubobject<UNDCombatComponent>(TEXT("CombatComponent"));
    AttacksComponent = CreateDefaultSubobject<UNDAttacksComponent>(TEXT("AttacksComponent"));

    bIsAttacking = false;
}

void ANDCombatCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (CombatComponent)
    {
        CombatComponent->OnSkillEnd.AddDynamic(this, &ANDCombatCharacter::OnAttackEnd);
    }
}

void ANDCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // ���� �Է� ���ε�
    PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard1);
    PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard2);
    PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard3);
    PlayerInputComponent->BindAction("Attack4", IE_Pressed, this, &ANDCombatCharacter::PressKeyboard4);
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

    bIsAttacking = true;

    // ��ų ����
    if (CombatComponent)
    {
        CombatComponent->ExecuteSkill(SkillName);
    }
}

void ANDCombatCharacter::OnAttackEnd()
{
    UE_LOG(LogTemp, Display, TEXT("NDCombatCharacter::OnAttackEnd()"));
    bIsAttacking = false;
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
    if (bIsAttacking) return;  // ���� �߿��� �̵� �Ұ�

    Super::MoveForward(Value);
}

void ANDCombatCharacter::MoveRight(float Value)
{
    if (bIsAttacking) return;  // ���� �߿��� �̵� �Ұ�

    Super::MoveRight(Value);
}
