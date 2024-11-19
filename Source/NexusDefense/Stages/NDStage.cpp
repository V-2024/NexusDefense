#include "NDStage.h"
#include "Manager/NDEventManager.h"
#include "Manager/NDDataManager.h"
#include "Manager/NDSpawnManager.h"
#include "Manager/NDObjectPoolManager.h"
#include "Manager/NDScoreManager.h"
#include "Kismet/GameplayStatics.h"

ANDStage::ANDStage()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentWave = 0;
    RemainingEnemies = 0;
    bIsStageActive = false;
    StageTimer = 0.0f;
}

void ANDStage::BeginPlay()
{
    Super::BeginPlay();

    //EventManager = Cast<UNDEventManager>(GetGameInstance()->GetSubsystem<UNDEventManager>());
    //DataManager = Cast<UNDDataManager>(GetGameInstance()->GetSubsystem<UNDDataManager>());
    ScoreManager = UNDScoreManager::GetInstance();
}

void ANDStage::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsStageActive)
    {
        StageTimer += DeltaTime;
    }
}

void ANDStage::Initialize(UStageData* InStageData, UNDSpawnManager* InSpawnManager, UNDObjectPoolManager* InObjectPoolManager)
{
    StageData = InStageData;
    SpawnManager = InSpawnManager;
    ObjectPoolManager = InObjectPoolManager;
    CurrentWave = 0;
    RemainingEnemies = 0;
    StageTimer = 0.0f;

    //SpawnManager->Initialize(this, ObjectPoolManager);
}

void ANDStage::StartStage()
{
    bIsStageActive = true;
    StartNextWave();
    if (EventManager)
    {
        EventManager->OnStageStarted.Broadcast(StageData->StageIndex);
    }
}

void ANDStage::EndStage()
{
    bIsStageActive = false;
    SpawnManager->StopSpawning();
    if (EventManager)
    {
        EventManager->TriggerStageCompleted(StageData->StageIndex);
    }
    ScoreManager->FinalizeStageScore(StageData->StageIndex);
}

void ANDStage::PauseStage()
{
    bIsStageActive = false;
    SpawnManager->StopSpawning();
}

void ANDStage::ResumeStage()
{
    bIsStageActive = true;
    SpawnManager->StartSpawning(this, StageData->Waves[CurrentWave - 1]);
}

void ANDStage::StartNextWave()
{
    if (CurrentWave < GetTotalWaves())
    {
        CurrentWave++;
        SpawnManager->StartSpawning(this, StageData->Waves[CurrentWave - 1]);
        if (EventManager)
        {
            EventManager->TriggerWaveStarted(StageData->StageIndex, CurrentWave);
        }
    }
    else
    {
        CheckStageCompletion();
    }
}

void ANDStage::OnEnemyDefeated(AActor* DefeatedEnemy)
{
    RemainingEnemies--;
    ScoreManager->AddScore(100); // ���� ����, �����δ� �� ������ ���� �ٸ��� ����
    if (EventManager)
    {
        EventManager->OnEnemyDefeated.Broadcast(DefeatedEnemy);
    }
    CheckWaveCompletion();
}

void ANDStage::CheckWaveCompletion()
{
    if (RemainingEnemies <= 0)
    {
        if (EventManager)
        {
            EventManager->OnWaveCompleted.Broadcast(StageData->StageIndex, CurrentWave);
        }
        StartNextWave();
    }
}

void ANDStage::CheckStageCompletion()
{
    if (CurrentWave >= GetTotalWaves() && RemainingEnemies <= 0)
    {
        if (EventManager)
        {
            EventManager->OnStageCompleted.Broadcast(StageData->StageIndex);
        }
        EndStage();
    }
}