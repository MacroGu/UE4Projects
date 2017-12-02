// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"



/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditAnywhere, Category="Setup")
	float MaxDegreePerSecond = 20.0f; 
	

	void MoveTurret(FVector AimDirection);

	float GetChangeYaw();

private:
	float ChangeYaw;
};
