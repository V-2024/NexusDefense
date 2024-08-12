// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDStageManager.h"
#include "Stages/NDStage.h"
#include "Stages/StageData.h"

ANDStageManager* ANDStageManager::Instance = nullptr;

ANDStageManager::ANDStageManager()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentStageIndex = -1;
}


void ANDStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	if(!Instance)
	{
		Instance = this;
		LoadStages();
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


void ANDStageManager::LoadStages()
{
	for (const TSoftObjectPtr<UStageData>& StageDataAsset : StageDataList)
	{
		if (UStageData* LoadedStageData = StageDataAsset.LoadSynchronous())
		{
			LoadedStages.Add(LoadedStageData);
		}
	}
}

void ANDStageManager::StartNextWave()
{
	CurrentStageIndex++;

	if (CurrentStageIndex < LoadedStages.Num())
	{
		CreateStage();
	}
	else
	{
		// All stages cleared
		UE_LOG(LogTemp, Warning, TEXT("All stages cleared!"));
	}
}

bool ANDStageManager::IsStageClreared() const
{
	return CurrentStage ? CurrentStage->IsStageCleared() : false;
}

void ANDStageManager::CreateStage()
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
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No more stages to create!"));
	}
}



