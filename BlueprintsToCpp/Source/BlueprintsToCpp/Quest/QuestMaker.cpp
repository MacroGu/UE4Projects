// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMaker.h"

// Sets default values
AQuestMaker::AQuestMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PaticleSystem"));

	SetRootComponent(Root);
	ParticleSystem->SetupAttachment(Root);
}


