// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	float ChangePitch = AimRotation.Pitch - CurrentRotation.Pitch;

	float RelativeSpeed = FMath::Clamp<float>(ChangePitch, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreePersecond * GetWorld()->DeltaTimeSeconds;
	float NewRotationPitch = RelativeRotation.Pitch + RotationChange;
	// limitation of Pitch
	NewRotationPitch = FMath::Clamp<float>(NewRotationPitch, MinDegree, MaxDegree);


	SetRelativeRotation(FRotator(NewRotationPitch,0,0));
}
