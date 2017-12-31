// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateActorVector.h"


// Sets default values
ARotateActorVector::ARotateActorVector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AngleAxis = 0;
}

// Called when the game starts or when spawned
void ARotateActorVector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotateActorVector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(0, 0, 800);

	FVector Radius = FVector(200,0,0);

	AngleAxis++;

	if(AngleAxis > 360.f)
	{
		AngleAxis = 1;
	}

	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0,0,1));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.X += RotateValue.Z;
	
	SetActorLocation(NewLocation);

}

