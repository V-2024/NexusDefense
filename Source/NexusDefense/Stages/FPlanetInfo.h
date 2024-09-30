// NDGameTypes.h

#pragma once

#include "CoreMinimal.h"
#include "FPlanetInfo.generated.h"

USTRUCT(BlueprintType)
struct FPlanetInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PlanetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* PlanetImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> StageIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D Position; // 항성계 지도에서의 위치

    FPlanetInfo()
        : PlanetName(TEXT("Unknown"))
        , Description(TEXT(""))
        , PlanetImage(nullptr)
        , bIsUnlocked(false)
        , Position(FVector2D::ZeroVector)
    {}
};