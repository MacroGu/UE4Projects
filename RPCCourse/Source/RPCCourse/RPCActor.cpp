// Fill out your copyright notice in the Description page of Project Settings.


#include "RPCActor.h"
#include "Kismet/GameplayStatics.h"
#include "ExCommon.h"
#include "CubeRelicateActor.h"
#include "CubeNoRelicateActor.h"


// Sets default values
ARPCActor::ARPCActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SetReplicates(false);
	bNetLoadOnClient = true;

}

// Called when the game starts or when spawned
void ARPCActor::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()->IsServer())
	{
		GetWorld()->SpawnActor<ACubeRelicateActor>(ACubeRelicateActor::StaticClass(), GetActorLocation() + FVector::RightVector * 300.f, FQuat::Identity.Rotator());


		GetWorld()->SpawnActor<ACubeNoRelicateActor>(ACubeNoRelicateActor::StaticClass(), GetActorLocation() - FVector::RightVector * 300.f, FQuat::Identity.Rotator());
	}
	
}

// Called every frame
void ARPCActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

