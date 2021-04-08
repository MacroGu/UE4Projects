// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeRelicateActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "ExCommon.h"

// Sets default values
ACubeRelicateActor::ACubeRelicateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// …Ë÷√∏¥÷∆
	SetReplicates(true);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticCubeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	CubeMesh->SetStaticMesh(StaticCubeMesh.Object);


}

// Called when the game starts or when spawned
void ACubeRelicateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeRelicateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

