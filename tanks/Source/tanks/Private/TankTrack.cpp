// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ThrottleToDrive = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1,1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = TankMaDrivingForce * ThrottleToDrive * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied,ForceLocation);
}
