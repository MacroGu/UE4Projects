// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpBase.h"


// Sets default values
APickUpBase::APickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionArea = CreateDefaultSubobject<USphereComponent>(FName("CollisionArea"));
	CollisionArea->SetSphereRadius(500.0f);
	RootComponent = CollisionArea;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionArea->bGenerateOverlapEvents = true;
	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnOverlap);
}

// Called every frame
void APickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpBase::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UseItem(OtherActor);
}

void APickUpBase::UseItem(AActor * User)
{
	CollisionArea->bGenerateOverlapEvents = false; // avoid repeat
	this->SetActorHiddenInGame(true);
}

