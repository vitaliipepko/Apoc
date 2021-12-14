// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApocGameMode.h"
#include "ApocPlayerController.h"
#include "ApocCharacter.h"
#include "UObject/ConstructorHelpers.h"

AApocGameMode::AApocGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AApocPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/BP_Character"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}