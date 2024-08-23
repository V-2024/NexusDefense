// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDStageManager.h"
#include "Stages/NDStage.h"
#include "Stages/StageData.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "NDEventManager.h"
#include "NDDataManager.h"

// 메모리 관리: 현재 스테이지 파괴 시 관련 리소스들이 정리되는지 확인
// 현재는 새 스테이지 생성 시 이전 스테이지를 파괴, 스테이지 상태를 저장하거나 캐싱 필요

ANDStageManager* ANDStageManager::Instance = nullptr;

ANDStageManager::ANDStageManager()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentStageIndex = -1;

	EventManager = UNDEventManager::GetInstance();
	DataManager = UNDDataManager::GetInstance();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Folder Path
	FString AssetFolderPath = FPaths::ProjectContentDir() + "/NexusDefense/Stages/";

	// Serach Folder Assets
	TArray<FAssetData> AssetDatas;

	AssetRegistry.GetAssetsByPath(*AssetFolderPath, AssetDatas, true);

	// Load UStageData
	for (const FAssetData& AssetData : AssetDatas)
	{
		// UStageData Check
		if (AssetData.GetClass()->IsChildOf(UStageData::StaticClass()))
		{
			UStageData* StageData = Cast<UStageData>(AssetData.GetAsset());
			if (StageData)
			{
				LoadedStages.Add(StageData);
			}
		}
	}
}


void ANDStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	if(!Instance)
	{
		Instance = this;
	}
	else
	{
		Destroy();
	}
}


ANDStageManager* ANDStageManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<ANDStageManager>();
		Instance->AddToRoot();
	}

	return Instance;
}


void ANDStageManager::LoadStages(int32 StageNum)
{

}

void ANDStageManager::StartNextWave()
{
	if (CurrentStage)
	{
		CurrentStage->StartNextWave();
		EventManager->OnWaveStart.Broadcast(CurrentStage->GetCurrentWave());
	}
}

bool ANDStageManager::IsStageClreared() const
{
	return CurrentStage ? CurrentStage->IsStageCleared() : false;
}

void ANDStageManager::CreateStage(int32 StageIndex)
{
	if (CurrentStage)
	{
		CurrentStage->Destroy();
	}

	if (CurrentStageIndex < LoadedStages.Num())
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			CurrentStage = World->SpawnActor<ANDStage>(ANDStage::StaticClass(), SpawnParams);
			CurrentStage->Initialize(LoadedStages[CurrentStageIndex]);
			CurrentStage->StartStage();

			EventManager->OnStageStart.Broadcast();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No more stages to create!"));
	}

	DataManager->SaveGameData();
}



