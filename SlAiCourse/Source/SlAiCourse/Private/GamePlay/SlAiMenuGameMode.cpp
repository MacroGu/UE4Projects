// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuGameMode.h"
#include "SlAiMenuHUD.h"
#include "SlAiMenuController.h"



ASlAiMenuGameMode::ASlAiMenuGameMode()
{
	PlayerControllerClass = ASlAiMenuController::StaticClass();
	HUDClass = ASlAiMenuHUD::StaticClass();


}
