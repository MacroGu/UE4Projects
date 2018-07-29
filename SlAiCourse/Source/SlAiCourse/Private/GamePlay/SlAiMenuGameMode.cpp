// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuGameMode.h"
#include "SlAiMenuHUD.h"
#include "SlAiMenuController.h"



#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"



ASlAiMenuGameMode::ASlAiMenuGameMode()
{
	PlayerControllerClass = ASlAiMenuController::StaticClass();
	HUDClass = ASlAiMenuHUD::StaticClass();
}

void ASlAiMenuGameMode::BeginPlay()
{
	Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("SlAiCourse");


}
