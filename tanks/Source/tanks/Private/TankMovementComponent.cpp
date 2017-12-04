// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (LeftTrackToSet == nullptr || RightTrackToSet == nullptr)
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throttle)
{
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}

void UTankMovementComponent::MoveRight(float Throttle)
{
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto MoveVelocityNormal = MoveVelocity.GetSafeNormal();
	auto AIForwardNormal = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIRightNormal = GetOwner()->GetActorRightVector();

	auto ForwardSpeed = FVector::DotProduct(MoveVelocity, AIForwardNormal); // -1 ~ 1
	auto RightSpeed = FVector::DotProduct(MoveVelocityNormal, AIRightNormal);

	MoveForward(ForwardSpeed);
	MoveRight(RightSpeed);
}
