// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"





/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreePersecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegree = 40.0;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinDegree = -5.0f;
};
