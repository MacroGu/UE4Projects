// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"








/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);  // -1 ~ 1

	void DriveTrack();

	void ApplySideForce();

	UPROPERTY(EditAnyWhere, Category="Setup")
	float TankMaDrivingForce = 40000000.0f;   // a = 1m/s   F = ma	
	
	float ThrottleToDrive = 0;
	
};
