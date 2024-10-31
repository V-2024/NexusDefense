
#include "AI/NDAITask.h"

FNDAITask::FNDAITask()
    : Enemy(nullptr)
    , Player(nullptr)
    , AttackRange(0.0f)
    , bInAttackRange(false)
    , TargetLocation(FVector::ZeroVector)
    , bShouldMove(false)
{
}
