// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NDEventManager.h"
#include "Enemy/NDEnemyBase.h"

UNDEventManager* UNDEventManager::Instance = nullptr;

UNDEventManager* UNDEventManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UNDEventManager>();
        Instance->AddToRoot();
    }
    return Instance;
}