// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatorActor.h"


// Sets default values
ARotatorActor::ARotatorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dimensions = FVector(300, 0, 0 );
	AxisVector = FVector(0,0,1);
	Multiplier = 50.f;



}

// Called when the game starts or when spawned
void ARotatorActor::BeginPlay()
{
	Super::BeginPlay();
	
}
 
// Called every frame
void ARotatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	AngleAxis += DeltaTime * Multiplier ;

	if(AngleAxis >= 360.0f)
	{
		AngleAxis = 0;
	}

	FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, AxisVector);

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;
	
	FRotator NewRotation = FRotator(0, AngleAxis, 0);

	FQuat QuatRoation = FQuat(NewRotation);
	SetActorLocationAndRotation(NewLocation, QuatRoation, false, 0, ETeleportType::None); 

}

