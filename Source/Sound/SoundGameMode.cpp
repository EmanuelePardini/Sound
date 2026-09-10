// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoundGameMode.h"
#include "SoundCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoundGameMode::ASoundGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
