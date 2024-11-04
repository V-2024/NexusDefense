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
    FThreadSafeBool bStopThread; // �����带 �����ϰ� ���߱� ���� ����
    FRunnableThread* Thread; // ����� ������

    FCriticalSection TaskLock; // �۾� ����� �����ϰ� �����ϱ� ���� �����ġ
    TQueue<FNDAITask> TaskQueue; // �ؾ� �� �۾����� �����ϴ� ��⿭
    TQueue<FNDAITask> CompletedTasks; // �Ϸ�� �۾����� �����ϴ� ��⿭

    void ProcessTask(FNDAITask& Task); // �۾��� ó���ϴ� �Լ�
};
