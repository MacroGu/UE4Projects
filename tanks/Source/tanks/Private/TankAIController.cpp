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
	if (GetControlledTank() && GetPlayerTank())
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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto ProcessedTank = Cast<ATank>(InPawn);
		if (!ProcessedTank)
		{
			return;
		}
		ProcessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnControlledTankDeath);
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

void ATankAIController::OnControlledTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Tank dead"));
	if (GetControlledTank())
	{
		GetControlledTank()->DetachFromControllerPendingDestroy();
	}

}
