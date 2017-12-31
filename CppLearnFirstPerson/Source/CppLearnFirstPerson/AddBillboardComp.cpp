// Fill out your copyright notice in the Description page of Project Settings.

#include "AddBillboardComp.h"

#include "Components/BillboardComponent.h"

// Sets default values
AAddBillboardComp::AAddBillboardComp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

 	MyBillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("My Billboard"));
	MyBillboardComp->SetHiddenInGame(false, true);
	RootComponent = MyBillboardComp;

}

// Called when the game starts or when spawned
void AAddBillboardComp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAddBillboardComp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

