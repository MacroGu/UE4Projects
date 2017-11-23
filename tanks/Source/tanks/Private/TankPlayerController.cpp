// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error, Controlled tank is null"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("controlled tank is %s"), *ControlledTank->GetName());
	}

}

void ATankPlayerController::Tick(float DelatTime)
{

	AimToTarget();
}

void ATankPlayerController::AimToTarget()
{
	// if getHitLocation
	// Tank-> MoveTowards 
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation)
{
	DeprojectScreenPositionToWorld

	return false;
}

ATank* ATankPlayerController::GetControlledTank()
{




	return Cast<ATank>(GetPawn());
}