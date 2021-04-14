// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MGmmorpgGameModeBase.h"
#include <ConstructorHelpers.h>


AMGmmorpgGameModeBase::AMGmmorpgGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
