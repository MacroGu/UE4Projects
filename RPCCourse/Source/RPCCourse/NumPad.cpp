// Fill out your copyright notice in the Description page of Project Settings.


#include "NumPad.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"



// Sets default values
ANumPad::ANumPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置不可复制
	SetReplicates(false);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(RootComponent);

	TextRender->SetWorldSize(80.f);
	TextRender->SetTextRenderColor(FColor::Red);
	TextRender->SetRelativeLocation(FVector(0.f, 0.f, 50.f));


}

void ANumPad::AssignRenderText(FString InText)
{
	TextRender->SetText(InText);

}

// Called when the game starts or when spawned
void ANumPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANumPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

