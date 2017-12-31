// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CppLearnFirstPersonGameMode.h"
#include "CppLearnFirstPersonHUD.h"
#include "CppLearnFirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppLearnFirstPersonGameMode::ACppLearnFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACppLearnFirstPersonHUD::StaticClass();
}
