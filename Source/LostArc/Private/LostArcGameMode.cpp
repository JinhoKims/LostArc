// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArcGameMode.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALostArcGameMode::ALostArcGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALostArcPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ArcCharacter/Player/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}