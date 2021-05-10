// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"


void AMyAIController::SetPlayerAlias(const FString& Alias)
{
	PlayerAlias_ = Alias;
}

FString AMyAIController::PlayerAlias()
{
	return PlayerAlias_;
}