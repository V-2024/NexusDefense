#include "NDStageManager.h"
#include "NDEventManager.h"
#include "NDDataManager.h"
#include "NDSpawnManager.h"
#include "NDObjectPoolManager.h"
#include "Stages/NDStage.h"
#include "Stages/StageData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/GameplayStatics.h"


ANDStageManager::ANDStageManager()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentStageIndex = -1;
}

void ANDStageManager::BeginPlay()
{
    Super::BeginPlay();

    //EventManager = Cast<UNDEventManager>(GetGameInstance()->GetSubsystem<UNDEventManager>());
    //DataManager = Cast<UNDDataManager>(GetGameInstance()->GetSubsystem<UNDDataManager>());

    //SpawnManager = Cast<ANDSpawnManager>(GetGameInstance()->GetSubsystem<ANDSpawnManager>());
    //ObjectPoolManager = Cast<ANDObjectPoolManager>(GetGameInstance()->GetSubsystem<ANDObjectPoolManager>());

    if (EventManager)
    {
        EventManager->OnStageCompleted.AddUObject(this, &ANDStageManager::OnStageCleared);
        EventManager->OnStageEnd.AddUObject(this, &ANDStageManager::OnStageFailed);
    }

    LoadStageData();
}

void ANDStageManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    CleanupCurrentStage();
}

void ANDStageManager::LoadStageData()
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    FString AssetFolderPath = FPaths::ProjectContentDir() + "/NexusDefense/Stages/";
    TArray<FAssetData> AssetDatas;
    AssetRegistry.GetAssetsByPath(*AssetFolderPath, AssetDatas, true);

    for (const FAssetData& AssetData : AssetDatas)
    {
        if (AssetData.GetClass()->IsChildOf(UStageData::StaticClass()))
        {
            if (UStageData* StageData = Cast<UStageData>(AssetData.GetAsset()))
            {
                LoadedStages.Add(StageData);
            }
        }
    }
}

void ANDStageManager::StartStage(int32 StageIndex)
{
    if (!LoadedStages.IsValidIndex(StageIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid stage index: %d"), StageIndex);
        return;
    }

    CleanupCurrentStage();
    CurrentStageIndex = StageIndex;

    UWorld* World = GetWorld();
    if (World)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        CurrentStage = World->SpawnActor<ANDStage>(ANDStage::StaticClass(), SpawnParams);
        if (CurrentStage)
        {
            CurrentStage->Initialize(LoadedStages[CurrentStageIndex], SpawnManager, ObjectPoolManager);
            CurrentStage->StartStage();

            if (EventManager)
            {
                EventManager->OnStageStarted.Broadcast(CurrentStageIndex);
            }
        }
    }
}

void ANDStageManager::EndCurrentStage()
{
    if (CurrentStage)
    {
        CurrentStage->EndStage();
        CleanupCurrentStage();
    }
}

void ANDStageManager::OnStageCleared(int32 StageIndex)
{
    UE_LOG(LogTemp, Log, TEXT("Stage %d cleared!"), StageIndex);

    if (DataManager)
    {
        //DataManager->UpdateStageProgress(StageIndex, true);
        DataManager->SaveGameData();
    }

    SetupNextStage();
}

void ANDStageManager::OnStageFailed(int32 StageIndex)
{
    UE_LOG(LogTemp, Log, TEXT("Stage %d failed!"), StageIndex);

    if (EventManager)
    {
        EventManager->OnGameOver.Broadcast();
    }
}

void ANDStageManager::CleanupCurrentStage()
{
    if (CurrentStage)
    {
        CurrentStage->EndStage();
        CurrentStage->Destroy();
        CurrentStage = nullptr;
    }
}

void ANDStageManager::SetupNextStage()
{
    CurrentStageIndex++;
    if (LoadedStages.IsValidIndex(CurrentStageIndex))
    {
        StartStage(CurrentStageIndex);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("All stages completed!"));
        if (EventManager)
        {
            //EventManager->OnAllStagesCompleted.Broadcast();
        }
    }
}