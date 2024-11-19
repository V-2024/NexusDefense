#include "NDStageManager.h"
#include "NDEventManager.h"
#include "NDDataManager.h"
#include "NDSpawnManager.h"
#include "NDObjectPoolManager.h"
#include "Stages/NDStage.h"
#include "Stages/StageData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/GameplayStatics.h"


UNDStageManager::UNDStageManager()
{
    CurrentStageIndex = -1;
}

//void ANDStageManager::BeginPlay()
//{
//    Super::BeginPlay();
//
//    //EventManager = Cast<UNDEventManager>(GetGameInstance()->GetSubsystem<UNDEventManager>());
//    //DataManager = Cast<UNDDataManager>(GetGameInstance()->GetSubsystem<UNDDataManager>());
//
//    //SpawnManager = Cast<ANDSpawnManager>(GetGameInstance()->GetSubsystem<ANDSpawnManager>());
//    //ObjectPoolManager = Cast<ANDObjectPoolManager>(GetGameInstance()->GetSubsystem<ANDObjectPoolManager>());
//
//    if (EventManager)
//    {
//        EventManager->OnStageCompleted.AddUObject(this, &ANDStageManager::OnStageCleared);
//        EventManager->OnStageEnd.AddUObject(this, &ANDStageManager::OnStageFailed);
//    }
//
//    LoadStageData();
//}

//void ANDStageManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//    Super::EndPlay(EndPlayReason);
//    CleanupCurrentStage();
//}

void UNDStageManager::LoadStageData()
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

void UNDStageManager::StartStage(int32 StageIndex)
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
        //SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        CurrentStage = World->SpawnActor<ANDStage>(ANDStage::StaticClass(), SpawnParams);
        if (CurrentStage)
        {
            CurrentStage->Initialize(LoadedStages[CurrentStageIndex], SpawnManager, ObjectPoolManager);
            CurrentStage->StartStage();

            if (EventManager)
            {
                EventManager->TriggerStageStarted(CurrentStageIndex);
            }
        }
    }
}

void UNDStageManager::EndCurrentStage()
{
    if (CurrentStage)
    {
        CurrentStage->EndStage();
        CleanupCurrentStage();
    }
}

void UNDStageManager::OnStageCleared(int32 StageIndex)
{
    UE_LOG(LogTemp, Log, TEXT("Stage %d cleared!"), StageIndex);

    if (DataManager)
    {
        //DataManager->UpdateStageProgress(StageIndex, true);
        DataManager->SaveGameData();
    }

    SetupNextStage();
}

void UNDStageManager::OnStageFailed(int32 StageIndex)
{
    UE_LOG(LogTemp, Log, TEXT("Stage %d failed!"), StageIndex);

    if (EventManager)
    {
        EventManager->OnGameOver.Broadcast();
    }
}

TArray<FPlanetInfo> UNDStageManager::GetPlanetInfos() const
{
    return PlanetInfos;
}

bool UNDStageManager::IsPlanetUnlocked(int32 PlanetIndex) const
{
    if (PlanetInfos.IsValidIndex(PlanetIndex))
    {
        return PlanetInfos[PlanetIndex].bIsUnlocked;
    }

    return false;
}

//void UNDStageManager::OnPlanetClicked(int32 PlanetIndex)
//{
//    if (PlanetInfos.IsValidIndex(PlanetIndex))
//	{
//		if (PlanetInfos[PlanetIndex].bIsUnlocked)
//		{
//			//EventManager->OnPlanetClicked.Broadcast(PlanetIndex);
//		}
//	}
//}

void UNDStageManager::CleanupCurrentStage()
{
    if (CurrentStage)
    {
        CurrentStage->EndStage();
        CurrentStage->Destroy();
        CurrentStage = nullptr;
    }
}

void UNDStageManager::InitializePlanetInfos()
{
    // Initialized the planet information
    // In practice, we need to load from a datatable or external file
    FPlanetInfo Planet1;
    Planet1.PlanetName = TEXT("Terra Prime");
    Planet1.Description = TEXT("A lush, Earth-like planet teeming with life.");
    Planet1.bIsUnlocked = true;
    Planet1.Position = FVector2D(100, 100);
    Planet1.StageIDs = { 1, 2, 3 };
    PlanetInfos.Add(Planet1);

    FPlanetInfo Planet2;
    Planet2.PlanetName = TEXT("Frozen Helios");
    Planet2.Description = TEXT("An icy world with hidden resources beneath its surface.");
    Planet2.bIsUnlocked = false;
    Planet2.Position = FVector2D(300, 200);
    Planet2.StageIDs = { 4, 5, 6 };
    PlanetInfos.Add(Planet2);

    // more planets...
}

void UNDStageManager::SetupNextStage()
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