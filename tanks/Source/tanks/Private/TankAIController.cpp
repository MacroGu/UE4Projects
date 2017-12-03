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


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetControlledTank())
	{
		// 让坦克 向玩家移动

		MoveToActor(GetPlayerTank(), AcceptenceRadius);

		// 炮塔转向玩家
		auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
		if (AimingComponent->FiringState == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
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
