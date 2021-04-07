// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPCCourseGameMode.h"
#include "RPCCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPCCourseGameMode::ARPCCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
