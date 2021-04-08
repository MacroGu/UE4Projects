// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeNoRelicateActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "ExCommon.h"


// Sets default values
ACubeNoRelicateActor::ACubeNoRelicateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// …Ë÷√∏¥÷∆
	SetReplicates(false);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticCubeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	CubeMesh->SetStaticMesh(StaticCubeMesh.Object);

}

// Called when the game starts or when spawned
void ACubeNoRelicateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeNoRelicateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

