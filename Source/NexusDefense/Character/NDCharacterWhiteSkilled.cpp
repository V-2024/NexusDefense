// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCharacterWhiteSkilled.h"

ANDCharacterWhiteSkilled::ANDCharacterWhiteSkilled()
{
    AttacksComponent = CreateDefaultSubobject<UNDAttacksComponent>(TEXT("AttacksComponent"));

    AttackRadius = 50.0f;
    AttackLength = 200.0f;

    AttackMontage1 = nullptr;
    AttackMontage2 = nullptr;
    AttackMontage3 = nullptr;
    AttackMontage4 = nullptr;
}

void ANDCharacterWhiteSkilled::ExecuteAttack(EAttackType AttackType)
{
    if (bAttacking)
    {
        return;
    }

    UAnimMontage* TargetMontage = GetAttackMontage(AttackType);
    if (!TargetMontage)
    {
        return;
    }

    bAttacking = true;
    CurrentAttackType = AttackType;

    CurrentAttackDamageInfo = GetAttackDamageInfo(AttackType);

    PlayAnimMontage(TargetMontage);
}

UAnimMontage* ANDCharacterWhiteSkilled::GetAttackMontage(EAttackType AttackType) const
{
    switch (AttackType)
    {
    case EAttackType::Attack1:
        return AttackMontage1;
    case EAttackType::Attack2:
        return AttackMontage2;
    case EAttackType::Attack3:
        return AttackMontage3;
    case EAttackType::Attack4:
        return AttackMontage4;
    default:
        return nullptr;
    }
}

void ANDCharacterWhiteSkilled::AttackEnd()
{
    bAttacking = false;
    CurrentAttackType = EAttackType::None;
}

FND_S_DamageInfo ANDCharacterWhiteSkilled::GetAttackDamageInfo(EAttackType AttackType) const
{
    FND_S_DamageInfo DamageInfo;
    DamageInfo.DamageType = E_DamageType::Melee;

    switch (AttackType)
    {
    case EAttackType::Attack1:
        DamageInfo.Amount = 10.0f;
        DamageInfo.DamageType = E_DamageType::Melee;
        DamageInfo.DamageResponse = E_DamageResponse::HitReaction;
        DamageInfo.CanBeBlocked = true;
        break;

    case EAttackType::Attack2:
        DamageInfo.Amount = 15.0f;
        DamageInfo.DamageType = E_DamageType::Melee;
        DamageInfo.DamageResponse = E_DamageResponse::KnockBack;
        DamageInfo.CanBeBlocked = true;
        DamageInfo.ShouldForceInterrupt = true;
        break;

    case EAttackType::Attack3:
        DamageInfo.Amount = 20.0f;
        DamageInfo.DamageType = E_DamageType::Projectile;
        DamageInfo.DamageResponse = E_DamageResponse::KnockBack;
        DamageInfo.ShouldDamageInvincible = true;
        break;

    case EAttackType::Attack4:
        DamageInfo.Amount = 25.0f;
        DamageInfo.DamageType = E_DamageType::Explosion;
        DamageInfo.DamageResponse = E_DamageResponse::KnockBack;
        DamageInfo.ShouldForceInterrupt = true;
        DamageInfo.ShouldDamageInvincible = true;
        break;

    default:
        DamageInfo.DamageType = E_DamageType::None;
        break;
    }

    return DamageInfo;
}

void ANDCharacterWhiteSkilled::ProcessAttack(EAttackType AttackType)
{

    if (!AttacksComponent)
    {
        return;
    }
    FND_S_AttackInfo AttackInfo;
    AttackInfo.DamageInfo = GetAttackDamageInfo(AttackType);
    AttackInfo.Montage = GetAttackMontage(AttackType);

    UE_LOG(LogTemp, Warning, TEXT("Damage Amount: %.1f"), AttackInfo.DamageInfo.Amount);
    UE_LOG(LogTemp, Warning, TEXT("Damage Type: %s"), *UEnum::GetValueAsString(AttackInfo.DamageInfo.DamageType));
    UE_LOG(LogTemp, Warning, TEXT("Damage Response: %s"), *UEnum::GetValueAsString(AttackInfo.DamageInfo.DamageResponse));

    UE_LOG(LogTemp, Warning, TEXT("AttackInfo Setup Complete - Montage: %s"),
        AttackInfo.Montage ? *AttackInfo.Montage->GetName() : TEXT("nullptr"));

    float CurrentRadius = AttackRadius;
    float CurrentLength = AttackLength;

    if (!AttacksComponent)
    {
        return;
    }

    switch (AttackType)
    {
    case EAttackType::Attack1:
        AttacksComponent->PrimaryMeleeAttack(AttackInfo, AttackRadius, AttackLength);
        break;

    case EAttackType::Attack2:
        AttacksComponent->PrimaryMeleeAttack(AttackInfo, AttackRadius * 1.2f, AttackLength);
        break;

    case EAttackType::Attack3:
        AttacksComponent->PrimaryMeleeAttack(AttackInfo, AttackRadius * 2.0f, AttackLength);
        break;

    case EAttackType::Attack4:
        AttacksComponent->PrimaryMeleeAttack(AttackInfo, AttackRadius, AttackLength);
        break;
    }
}