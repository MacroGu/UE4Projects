// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTrack.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"






/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float Throttle);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
