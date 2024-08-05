// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NDGameMode.h"

ANDGameMode::ANDGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("문제없음"))
	//	DefaultPawnClass = ThirdPersonClassRef.Class;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("문제있음"))
	//}

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/NexusDefense.NDCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/NexusDefense.NDPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
