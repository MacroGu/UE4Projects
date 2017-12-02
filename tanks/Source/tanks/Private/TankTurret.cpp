// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::MoveTurret(FVector AimDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	ChangeYaw = AimRotation.Yaw - CurrentRotation.Yaw;
	// ==0 >0 <0

	if (ChangeYaw > 180)
	{
		ChangeYaw = ChangeYaw - 360;
	}
	else if (ChangeYaw < -180)
 	{
		ChangeYaw = ChangeYaw + 360;
	}

	float RelativeSpeed = FMath::Clamp<float>(ChangeYaw, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotationYaw = RotationChange + CurrentRotation.Yaw;



	SetRelativeRotation(FRotator(0, NewRotationYaw, 0));


}

float UTankTurret::GetChangeYaw()
{
	return this->ChangeYaw;
}
