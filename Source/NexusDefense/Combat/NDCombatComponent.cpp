
#include "Combat/NDCombatComponent.h"
#include "GameFramework/Character.h"

UNDCombatComponent::UNDCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentState = ECombatState::None;
}

void UNDCombatComponent::BeginPlay()
{
    Super::BeginPlay();
    OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UNDCombatComponent::SetCurrentState(ECombatState NewState)
{
    if (CurrentState != NewState)
    {
        CurrentState = NewState;
        OnCombatStateChanged.Broadcast(CurrentState);
    }
}