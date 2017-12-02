// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"







/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DelatTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank();
	
	void AimToTarget();

	bool GetSightRayHitLocation(FVector &outHitLocation);

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation);

private:
	float CrosshairXLocation = 0.5f;
	float CrosshairYLocation = 0.3f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
};
