// Copyright Epic Games, Inc. All Rights Reserved.

#include "DPGameMode.h"
#include "DPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADPGameMode::ADPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
