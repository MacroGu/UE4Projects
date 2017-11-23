// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (nullptr == ControlledTank || nullptr == GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Error, Controlled Tank is null"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is: %s, Player Tank is:%s "), 
			*ControlledTank->GetName(), *PlayerTank->GetName());
	}

}


ATank* ATankAIController::GetControlledTank()
{

	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank()
{
	ATank* playerTank =  Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (playerTank == nullptr)
	{
		return nullptr;
	}

	return playerTank;
}
