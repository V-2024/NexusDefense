// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FStageInfo.generated.h"

USTRUCT(BlueprintType)
struct FStageInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCompleted;

    // �߰����� �������� ���� (���̵�, ���� ��)

    FStageInfo()
        : Name(TEXT("Unknown"))
        , Icon(nullptr)
        , bIsUnlocked(false)
        , bIsCompleted(false)
    {}
};

