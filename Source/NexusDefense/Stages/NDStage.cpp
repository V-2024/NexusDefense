// Fill out your copyright notice in the Description page of Project Settings.


#include "Stages/NDStage.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/NDEventManager.h"
#include "Manager/NDDataManager.h"


// 비동기 레벨 로딩 고려 가능
// 적 스폰 로직 추가
// 스테이지 클리어 로직 추가
// 스테이지 종료 로직 추가
// 스테이지 시작 로직 추가
// 스테이지 데이터 로딩 로직 추가
// 스테이지 데이터 저장 로직 추가
// 스테이지 데이터 초기화 로직 추가
// bIsStageActive 상태 체크 추가
// 메모리관리: 스테이지데이터가 언제 해제되는지 명확하지 않음. 스테이지 종료 시 정리작업 수행
// 중간 저장 기능 추가

ANDStage::ANDStage()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentWave = 0;
	RemainingEnemies = 0;
	bIsStageActive = false;

	EventManager = UNDEventManager::GetInstance();
	DataManager = UNDDataManager::GetInstance();
}

void ANDStage::BeginPlay()
{
	Super::BeginPlay();
}

void ANDStage::Initialize(UStageData* InStageData)
{
	StageData = InStageData;
}

void ANDStage::StartStage()
{
	if (!StageData)
	{
		UE_LOG(LogTemp, Error, TEXT("StageData is not set!"));
		return;
	}

	// open Stage Level
	UGameplayStatics::OpenLevel(GetWorld(), *StageData->LevelFath);

	bIsStageActive = true;
	CurrentWave = 0;
	StartNextWave();

	//EventManager->OnStageStart.Broadcast();
}

void ANDStage::EndStage()
{
	bIsStageActive = false;
	//EventManager->OnStageEnd.Broadcast();
	DataManager->SaveGameData();

	// Add end stage rogic
}

bool ANDStage::IsStageCleared() const
{
	return CurrentWave >= StageData->Waves.Num() && RemainingEnemies == 0;
}


void ANDStage::OnEnemyDefeated()
{
	RemainingEnemies--;

	if (RemainingEnemies <= 0)
	{
		CheckWaveCompletion();
	}
}

void ANDStage::StartNextWave()
{
	if (CurrentWave >= StageData->Waves.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("No more waves to start!"));
		return;
	}

	RemainingEnemies = StageData->Waves[CurrentWave].EnemyCount;
	//EventManager->OnWaveStart.Broadcast(CurrentWave);
}

void ANDStage::CheckWaveCompletion()
{
	CurrentWave++;

	if (CurrentWave < StageData->Waves.Num())
	{
		StartNextWave();
	}
	else
	{
		EndStage();
	}
}


