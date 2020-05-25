// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestTriggerPick.h"

// Sets default values for this component's properties
UQuestTriggerPick::UQuestTriggerPick()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestTriggerPick::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UQuestTriggerPick::PickUp()
{

}

// Called every frame
void UQuestTriggerPick::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

