// Fill out your copyright notice in the Description page of Project Settings.


#include "RPCController.h"
#include "ExCommon.h"


void ARPCController::BeginPlay()
{
	Super::BeginPlay();

	FString SrceenCommand = FString("r.setres 1280x720w");
	ConsoleCommand(SrceenCommand);


	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	EchoNetMode();
}

void ARPCController::EchoNetMode()
{
	ENetMode NetMode = GetNetMode();
	switch (NetMode)
	{
	case NM_Standalone:
		DDH::Debug() << "NM_Standalone" << DDH::Endl();
		break;
	case NM_DedicatedServer:
		DDH::Debug() << "NM_DedicatedServer" << DDH::Endl();
		break;
	case NM_ListenServer:
		DDH::Debug() << "NM_ListenServer" << DDH::Endl();
		break;
	case NM_Client:
		DDH::Debug() << "NM_Client" << DDH::Endl();
		break;
	case NM_MAX:
		DDH::Debug() << "NM_MAX" << DDH::Endl();
		break;
	default:
		DDH::Debug() << "default" << DDH::Endl();
		break;
	}



}
