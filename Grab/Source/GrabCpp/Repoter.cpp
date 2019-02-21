// Fill out your copyright notice in the Description page of Project Settings.

#include "Repoter.h"


// Sets default values for this component's properties
URepoter::URepoter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URepoter::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;

	FString name = Owner->GetName();
	FVector Location = Owner->GetActorLocation();
	//UE_LOG(LogTemp, Error, TEXT("current Actor name: %s, location: %s"), *name, *Location.ToString());

	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	
}


// Called every frame
void URepoter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

