// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ReplTestGameMode.h"
#include "ReplTestPlayerController.h"
#include "ReplTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyAIController.h"
#include "MyHUD.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

AReplTestGameMode::AReplTestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AReplTestPlayerController::StaticClass();

	DefaultPawnClass = NULL;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		CharClass = PlayerPawnBPClass.Class;
	}

	PlayerCount = 0;

	SpawnLoc = FVector(-500.f, -90.f, 300.f);
	SpawnRot = FRotator(0.f, 0.f, 0.f);

	HUDClass = AMyHUD::StaticClass();
}

FString AReplTestGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString Rs = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if (AReplTestPlayerController* RTPC = Cast<AReplTestPlayerController>(NewPlayerController))
	{
		FString Alias = UGameplayStatics::ParseOption(Options, TEXT("Alias")).TrimStartAndEnd();
		if (Alias.Len() == 0 || AliasMap.Find(Alias))
		{
			return Rs;
		}

		RTPC->SetPlayerAlias(Alias);
		
		PlayerData Data;
		Data.Alias = Alias;
		AliasMap.Add(Alias, Data);
	}

	return Rs;
}

APlayerController* AReplTestGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AReplTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNetMode() == NM_DedicatedServer)
	{
		PlayerCount++;
		if (CharClass)
		{
			if (AReplTestCharacter* Player = GetWorld()->SpawnActor<AReplTestCharacter>(CharClass, SpawnLoc, SpawnRot))
			{
				PlayerList.Add(Player);

				/*if (AMyAIController* AIC = GetWorld()->SpawnActor<AMyAIController>(SpawnLoc, SpawnRot))
				{
					AIC->Possess(Player);
				}*/

				Player->SpawnDefaultController();

				//设置角色的显示名称
				if (AReplTestPlayerController* RTPC = Cast<AReplTestPlayerController>(NewPlayer))
				{
					if (PlayerData* Data = AliasMap.Find(RTPC->PlayerAlias()))
					{
						Player->SetAlias(*(Data->Alias));
						Data->RTC = Player;

						if (AMyAIController* AIC = Cast<AMyAIController>(Player->GetController()))
						{
							AIC->SetPlayerAlias(Data->Alias);
						}
					}
				}
			}
		}
	}
}
