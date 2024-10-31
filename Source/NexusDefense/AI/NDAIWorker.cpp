
#include "AI/NDAIWorker.h"

UNDAIWorker::UNDAIWorker()
    : Thread(nullptr)
    , bStopThread(false)
{
    Thread = FRunnableThread::Create(this, TEXT("NDAIWorker"), 0, TPri_Normal);
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Created"));
}

UNDAIWorker::~UNDAIWorker()
{
    if (Thread)
    {
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }
}

bool UNDAIWorker::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Initialized"));
    return true;
}

uint32 UNDAIWorker::Run()
{
    while (!bStopThread)
    {
        FNDAITask Task;
        bool bHasTask = false;

        {
            FScopeLock Lock(&TaskLock);
            bHasTask = TaskQueue.Dequeue(Task);
        }

        if (bHasTask)
        {
            ProcessTask(Task);
        }
        else
        {
            FPlatformProcess::Sleep(0.01f);
        }
    }

    return 0;
}

void UNDAIWorker::Stop()
{
    bStopThread = true;
}

void UNDAIWorker::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Exited"));
}

void UNDAIWorker::AddTask(const FNDAITask& NewTask)
{
    FScopeLock Lock(&TaskLock);
    TaskQueue.Enqueue(NewTask);
}

bool UNDAIWorker::GetCompletedTask(FNDAITask& OutTask)
{
    FScopeLock Lock(&TaskLock);
    return CompletedTasks.Dequeue(OutTask);
}

void UNDAIWorker::ProcessTask(FNDAITask& Task)
{
    if (!Task.Enemy || !Task.Player)
        return;

    float Distance = FVector::Distance(
        Task.Enemy->GetActorLocation(),
        Task.Player->GetActorLocation()
    );

    Task.bInAttackRange = (Distance <= Task.AttackRange);

    if (!Task.bInAttackRange)
    {
        Task.bShouldMove = true;
        Task.TargetLocation = Task.Player->GetActorLocation();
    }

    FScopeLock Lock(&TaskLock);
    CompletedTasks.Enqueue(Task);
}