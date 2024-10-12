// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDService.generated.h"

class UNDGameInstance;

// 서비스의 현재 상태를 나타내는 열거형
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
    // 서비스 초기화
    virtual void Initialize(UNDGameInstance* GameInstance) = 0;

    // 서비스 종료
    virtual void Shutdown() = 0;

    // 서비스 일시 중지
    virtual void Pause() = 0;

    // 서비스 재개
    virtual void Resume() = 0;

    // 서비스 상태 확인
    virtual ENDServiceStatus GetStatus() const = 0;

    // 서비스 이름 반환 (디버깅 및 로깅 목적)
    virtual FString GetServiceName() const = 0;

    // 서비스가 초기화되었는지 확인
    virtual bool IsInitialized() const = 0;

    // 서비스가 실행 중인지 확인
    virtual bool IsRunning() const = 0;
};
