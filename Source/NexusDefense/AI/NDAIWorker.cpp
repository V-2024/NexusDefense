
#include "AI/NDAIWorker.h"

FNDAIWorker::FNDAIWorker()
    : bStopThread(false)
    , Thread(nullptr)
{
    Thread = FRunnableThread::Create(this, TEXT("NDAIWorker"), 0, TPri_Normal);
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Created"));
}

FNDAIWorker::~FNDAIWorker()
{
    if (Thread)
    {
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }
}

bool FNDAIWorker::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Initialized"));
    return true;
}

uint32 FNDAIWorker::Run()
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

void FNDAIWorker::Stop()
{
    bStopThread = true;
}

void FNDAIWorker::Exit()
{
    UE_LOG(LogTemp, Warning, TEXT("ND AI Worker Thread Exited"));
}

void FNDAIWorker::AddTask(const FNDAITask& NewTask)
{
    FScopeLock Lock(&TaskLock);
    TaskQueue.Enqueue(NewTask);
}

bool FNDAIWorker::GetCompletedTask(FNDAITask& OutTask)
{
    FScopeLock Lock(&TaskLock);
    return CompletedTasks.Dequeue(OutTask);
}

void FNDAIWorker::ProcessTask(FNDAITask& Task)
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