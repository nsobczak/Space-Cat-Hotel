// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceCatRTSGameMode.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Character/SpaceCatRTSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceCatRTSGameMode::ASpaceCatRTSGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASpaceCatRTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}