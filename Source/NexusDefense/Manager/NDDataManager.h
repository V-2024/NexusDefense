#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NDDataManager.generated.h"

class UNDSaveGame;

UCLASS()
class NEXUSDEFENSE_API UNDDataManager : public UObject
{
    GENERATED_BODY()

public:
    static UNDDataManager* GetInstance();

    void Initialize();
    void SaveGameData();
    void LoadGameData();
    void StartNewGame();

    void SetPlayerScore(int32 Score);
    int32 GetPlayerScore() const;

    void SetCurrentLevel(int32 Level);
    int32 GetCurrentLevel() const;

    void UnlockStage(int32 StageNumber);
    bool IsStageUnlocked(int32 StageNumber) const;
    TArray<int32> GetUnlockedStages() const;


private:
    UNDDataManager();


private:
    
    static UNDDataManager* Instance;

    UPROPERTY()
    UNDSaveGame* CurrentSaveGame;

    FString SaveSlotName;
    uint32 UserIndex;

    // Game state variables
    int32 PlayerScore;
    int32 CurrentLevel;
    TArray<int32> UnlockedStages;

    // Add more game state variables as needed
};