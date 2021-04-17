// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "RPCInstance.h"



void UMenuWidget::AssignRPCInstance(URPCInstance* InInstance)
{
	RPCInstance = InInstance;
}

void UMenuWidget::LANServerEvent()
{
	RPCInstance->HostSession();
}

void UMenuWidget::LANClientEvent()
{
	RPCInstance->ClientSession();
}
