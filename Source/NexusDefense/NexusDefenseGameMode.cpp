// Copyright Epic Games, Inc. All Rights Reserved.

#include "NexusDefenseGameMode.h"
#include "NexusDefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANexusDefenseGameMode::ANexusDefenseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
