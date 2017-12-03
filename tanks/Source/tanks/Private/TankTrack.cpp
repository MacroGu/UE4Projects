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
	ApplySideForce();
}

void UTankTrack::SetThrottle(float Throttle)
{
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1,1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = TankMaDrivingForce * ThrottleToDrive * GetForwardVector();
	auto ForceLocation = GetSocketLocation(FName("ForceLocation"));
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied,ForceLocation);
}

void UTankTrack::ApplySideForce()
{
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// 找到坦克的移动方向 和速度
	auto TankVelocity = RootComponent->GetComponentVelocity();
	auto RightVector = RootComponent->GetRightVector();
	// 找到 坦克侧滑的速度
	auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);
	
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	// 找到坦克侧滑对应的加速度
	auto SideSpeedAcceleration = -SideSpeed / DeltaTime * GetRightVector();

	// F = ma
	auto CorrectionForce = (RootComponent->GetMass() * SideSpeedAcceleration) / 2;
	RootComponent->AddForce(CorrectionForce);

}
