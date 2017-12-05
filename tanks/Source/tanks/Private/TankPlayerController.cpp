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
	// Move to aim location
	Super::Tick(DelatTime);
	AimToTarget();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto ProcessedTank = Cast<ATank>(InPawn);
		if (!ProcessedTank)
		{
			return;
		}
		ProcessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
}

void ATankPlayerController::AimToTarget()
{
	if (!GetPawn())
	{
		return;
	}

	// if getHitLocation
	// Tank-> MoveTowards 
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	// Get Screen Size
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	FVector WorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{// 使用射线找撞击点
		return GetLookVectorHitLocation(WorldDirection, outHitLocation);
	}

	return false;
}

// 寻找射线撞击的点
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0.0f);
	return false;
}

void ATankPlayerController::TankResPawn()
{
	GetWorldTimerManager().ClearTimer(TankRespawnHandle);
	TArray<AActor* > PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	AActor* SpawnTarget = PlayerStarts[0];

	if (MyTank == nullptr )
	{
		return;
	}
	MyTank->ResetHealth();
	MyTank->SetActorTransform(SpawnTarget->GetTransform());
	Possess(MyTank);
	PlayerState->bIsSpectator = false;
	ChangeState(NAME_Playing);
}

void ATankPlayerController::OnControlledTankDeath()
{
	MyTank = GetControlledTank();
	// StartSpectatingOnly();
	PlayerState->bIsSpectator = true;
	ChangeState(NAME_Spectating);

	GetWorldTimerManager().SetTimer(TankRespawnHandle, this, &ATankPlayerController::TankResPawn, RespawnTime, false);

}

ATank* ATankPlayerController::GetControlledTank()
{

	return Cast<ATank>(GetPawn());
}