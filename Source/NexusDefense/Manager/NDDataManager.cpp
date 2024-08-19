// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDDataManager.h"

UNDDataManager* UNDDataManager::Instance = nullptr;

UNDDataManager* UNDDataManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UNDDataManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UNDDataManager::SaveGameData()
{
    // Implement save logic
}

void UNDDataManager::LoadGameData()
{
    // Implement load logic
}