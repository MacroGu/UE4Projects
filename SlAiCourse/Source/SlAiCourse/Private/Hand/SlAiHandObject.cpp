// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
ASlAiHandObject::ASlAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;


	// 给模型组件加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Axe_01.SM_Wep_Axe_01'"));

	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

