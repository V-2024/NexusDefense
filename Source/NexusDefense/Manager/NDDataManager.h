// NDDataManager.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDDataManager.generated.h"

UCLASS()
class NEXUSDEFENSE_API UNDDataManager : public UObject
{
    GENERATED_BODY()

public:
    static UNDDataManager* GetInstance();

    void SaveGameData();
    void LoadGameData();

    // Add getters and setters for game data

private:
    static UNDDataManager* Instance;

    // Add variables to store game data
};


