// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonSiegeRemakeGameMode.h"
#include "DungeonSiegeRemakePlayerController.h"
#include "DungeonSiegeRemakeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonSiegeRemakeGameMode::ADungeonSiegeRemakeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADungeonSiegeRemakePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}