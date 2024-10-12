// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDService.generated.h"

class UNDGameInstance;

// ������ ���� ���¸� ��Ÿ���� ������
UENUM(BlueprintType)
enum class ENDServiceStatus : uint8
{
    Uninitialized UMETA(DisplayName = "Uninitialized"),
    Initializing UMETA(DisplayName = "Initializing"),
    Running UMETA(DisplayName = "Running"),
    Paused UMETA(DisplayName = "Paused"),
    ShuttingDown UMETA(DisplayName = "Shutting Down"),
    Shutdown UMETA(DisplayName = "Shutdown")
};


UINTERFACE(MinimalAPI)
class UNDService : public UInterface
{
	GENERATED_BODY()
};


class NEXUSDEFENSE_API INDService
{
	GENERATED_BODY()

public:
    // ���� �ʱ�ȭ
    virtual void Initialize(UNDGameInstance* GameInstance) = 0;

    // ���� ����
    virtual void Shutdown() = 0;

    // ���� �Ͻ� ����
    virtual void Pause() = 0;

    // ���� �簳
    virtual void Resume() = 0;

    // ���� ���� Ȯ��
    virtual ENDServiceStatus GetStatus() const = 0;

    // ���� �̸� ��ȯ (����� �� �α� ����)
    virtual FString GetServiceName() const = 0;

    // ���񽺰� �ʱ�ȭ�Ǿ����� Ȯ��
    virtual bool IsInitialized() const = 0;

    // ���񽺰� ���� ������ Ȯ��
    virtual bool IsRunning() const = 0;
};
