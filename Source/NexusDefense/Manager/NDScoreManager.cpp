// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDScoreManager.h"

// 이벤트 시스템 연동, 점수 변경 시 알림
// 스레드 안정성 고려
// 점수 검증 로직
// 하이스코어 시스템
// 점수 계산 로직 추가: 콤보, 멀티플라이어 등
// 리더보드: 멀티플레이 환경에서 다른 플레이어의 점수를 실시간으로 확인할 수 있도록
// 메모리관리: AddToRoot()를 사용하므로 게임 종료 시 적절히 해제

UNDScoreManager* UNDScoreManager::Instance = nullptr;

UNDScoreManager* UNDScoreManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UNDScoreManager>();
		Instance->AddToRoot();
	}

	return Instance;
}

void UNDScoreManager::AddScore(int32 ScoreToAdd)
{
	CurrentScore += ScoreToAdd;
}

void UNDScoreManager::ResetScore()
{
	CurrentScore = 0;
	StageScores.Empty();
}

int32 UNDScoreManager::GetCurrentScore() const
{
	return CurrentScore;
}

void UNDScoreManager::FinalizeStageScore(int32 StageNumber)
{
	StageScores.Add(StageNumber, CurrentScore);
	//UNDDataManager::GetInstance()->SaveStageScore(StageNumber, CurrentScore);
	//UNDEventManager::GetInstance()->BroadcastStageScoreFinalized(StageNumber, CurrentScore);
}

UNDScoreManager::UNDScoreManager() : CurrentScore(0)
{
}

