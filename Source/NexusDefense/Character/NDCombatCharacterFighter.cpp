// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NDCombatCharacterFighter.h"

ANDCombatCharacterFighter::ANDCombatCharacterFighter()
{
    // �޺� ������Ʈ ����
    ComboComponent = CreateDefaultSubobject<UNDComboComponent>(TEXT("ComboComponent"));
}

void ANDCombatCharacterFighter::BeginPlay()
{
    Super::BeginPlay();

    // �޺� ������ ����
    if (ComboComponent && ComboActionData && ComboActionMontage)
    {
        ComboComponent->SetComboData(ComboActionData);
        ComboComponent->SetComboMontage(ComboActionMontage);
    }
}

void ANDCombatCharacterFighter::PressLMB()
{
    if (ComboComponent)
    {
        ComboComponent->ProcessComboCommand();
    }
}

void ANDCombatCharacterFighter::PressKeyboard1()
{
    HandleAttack(FName("FighterSkillA"));
}

void ANDCombatCharacterFighter::PressKeyboard2()
{
    HandleAttack(FName("FighterSkillB"));
}

void ANDCombatCharacterFighter::PressKeyboard3()
{
    HandleAttack(FName("FighterSkillC"));
}

void ANDCombatCharacterFighter::PressKeyboard4()
{
    HandleAttack(FName("FighterSkillD"));
}