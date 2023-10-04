// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomUtilitiesGameMode.h"
#include "CustomUtilitiesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACustomUtilitiesGameMode::ACustomUtilitiesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
