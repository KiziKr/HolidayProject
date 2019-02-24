// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Heroes/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
