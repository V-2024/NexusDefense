#include "Manager/NDDataManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "Data/NDSaveGame.h"

UNDDataManager* UNDDataManager::Instance = nullptr;

UNDDataManager::UNDDataManager()
{
    CurrentSaveGame = nullptr;
    SaveSlotName = "NDSaveSlot";
    UserIndex = 0;
}

UNDDataManager* UNDDataManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UNDDataManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UNDDataManager::Initialize()
{
    LoadGameData();
}

void UNDDataManager::SaveGameData()
{
    if (!CurrentSaveGame)
    {
        CurrentSaveGame = Cast<UNDSaveGame>(UGameplayStatics::CreateSaveGameObject(UNDSaveGame::StaticClass()));
    }

    if (CurrentSaveGame)
    {
        // Save current game state to CurrentSaveGame
        CurrentSaveGame->PlayerScore = PlayerScore;
        CurrentSaveGame->CurrentLevel = CurrentLevel;
        CurrentSaveGame->UnlockedStages = UnlockedStages;
        // Add more data fields as needed

        if (UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, UserIndex))
        {
            UE_LOG(LogTemp, Log, TEXT("Game saved successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to save game."));
        }
    }
}

void UNDDataManager::LoadGameData()
{
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        CurrentSaveGame = Cast<UNDSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
        if (CurrentSaveGame)
        {
            // Load game state from CurrentSaveGame
            PlayerScore = CurrentSaveGame->PlayerScore;
            CurrentLevel = CurrentSaveGame->CurrentLevel;
            UnlockedStages = CurrentSaveGame->UnlockedStages;
            // Load more data fields as needed

            UE_LOG(LogTemp, Log, TEXT("Game loaded successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load game."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No save game found. Starting new game."));
        StartNewGame();
    }
}

void UNDDataManager::StartNewGame()
{
    // Initialize new game state
    PlayerScore = 0;
    CurrentLevel = 1;
    UnlockedStages.Empty();
    UnlockedStages.Add(1); // Unlock first stage
    // Initialize more fields as needed

    SaveGameData(); // Save the initial state
}

void UNDDataManager::SetPlayerScore(int32 Score)
{
    PlayerScore = Score;
}

int32 UNDDataManager::GetPlayerScore() const
{
    return PlayerScore;
}

void UNDDataManager::SetCurrentLevel(int32 Level)
{
    CurrentLevel = Level;
}

int32 UNDDataManager::GetCurrentLevel() const
{
    return CurrentLevel;
}

void UNDDataManager::UnlockStage(int32 StageNumber)
{
    if (!UnlockedStages.Contains(StageNumber))
    {
        UnlockedStages.Add(StageNumber);
        SaveGameData(); // Save whenever we unlock a new stage
    }
}

bool UNDDataManager::IsStageUnlocked(int32 StageNumber) const
{
    return UnlockedStages.Contains(StageNumber);
}

TArray<int32> UNDDataManager::GetUnlockedStages() const
{
    return UnlockedStages;
}