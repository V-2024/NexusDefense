// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "AI/NDAITask.h"
#include "NDAIWorker.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDAIWorker : public UObject, public FRunnable
{
    GENERATED_BODY()

public:
    UNDAIWorker();
    virtual ~UNDAIWorker();

    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    void AddTask(const FNDAITask& NewTask);
    bool GetCompletedTask(FNDAITask& OutTask);

private:
    FThreadSafeBool bStopThread; // 스레드를 안전하게 멈추기 위한 변수
    FRunnableThread* Thread; // 실행될 스레드

    FCriticalSection TaskLock; // 작업 목록을 안전하게 관리하기 위한 잠금장치
    TQueue<FNDAITask> TaskQueue; // 해야 할 작업들을 보관하는 대기열
    TQueue<FNDAITask> CompletedTasks; // 완료된 작업들을 보관하는 대기열

    void ProcessTask(FNDAITask& Task); // 작업을 처리하는 함수
};
