// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReplTestGameMode.generated.h"

class AReplTestCharacter;
class AAIController;

struct PlayerData
{
	PlayerData()
	{
		RTC = NULL;
	}

	FString Alias;
	AReplTestCharacter* RTC;
};

UCLASS(minimalapi)
class AReplTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AReplTestGameMode();

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer);

private:

	int PlayerCount;

	TSubclassOf<AReplTestCharacter> CharClass;

	FVector SpawnLoc;
	FRotator SpawnRot;

	TArray<AReplTestCharacter*> PlayerList;

	TMap<FString, PlayerData> AliasMap;
};



