
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDBaseWeapon.generated.h"

UCLASS()
class NEXUSDEFENSE_API ANDBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ANDBaseWeapon();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
    USkeletalMeshComponent* SkeletalMesh;
};
