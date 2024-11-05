// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDAIManager.h"
#include "Enemy/NDEnemy.h"
#include "Kismet/GameplayStatics.h"

void UNDAIManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // AI Worker ����
    AIWorker = MakeShared<FNDAIWorker>();

    // ��� ó���� ���� Ÿ�̸� ����
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            ProcessTasksTimerHandle,
            this,
            &UNDAIManager::ProcessCompletedTasks,
            0.016f,  // 60fps
            true
        );
    }

    UE_LOG(LogTemp, Warning, TEXT("AI Manager Initialized"));
}

void UNDAIManager::Deinitialize()
{
    if (AIWorker)
    {
        AIWorker->Stop();
        AIWorker.Reset();
    }

    Super::Deinitialize();
}

void UNDAIManager::RequestAIUpdate(ANDEnemy* Enemy)
{
    if (!Enemy || !AIWorker)
    {
        return;
    }

    FNDAITask NewTask;
    NewTask.Enemy = Enemy;
    NewTask.Player = UGameplayStatics::GetPlayerCharacter(Enemy, 0);
    NewTask.AttackRange = Enemy->GetAttackRange(); // Enemy�� �� �Լ� �ʿ�

    AIWorker->AddTask(NewTask);
}

void UNDAIManager::ProcessCompletedTasks()
{
    if (!AIWorker)
        return;

    FNDAITask CompletedTask;
    while (AIWorker->GetCompletedTask(CompletedTask))
    {
        if (CompletedTask.Enemy)
        {
            // Enemy���� ��� ����
            CompletedTask.Enemy->ExecuteAIResult(CompletedTask);
            UE_LOG(LogTemp, Warning, TEXT("AI Task Completed - Enemy: %s, InRange: %s"),
                *CompletedTask.Enemy->GetName(),
                CompletedTask.bInAttackRange ? TEXT("True") : TEXT("False"));
        }
    }
}