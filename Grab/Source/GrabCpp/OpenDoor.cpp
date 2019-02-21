// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// call function from blueprint
	FString cmd = FString::Printf(TEXT("TestFuncFromBP paramterABCDS"));
	FOutputDeviceDebug device;
	CallFunctionByNameWithArguments(*cmd, device, NULL, true);


}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 每一帧 判断， 需要开门还是关门
	if (TriggerArea == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerArea is null."));
		return;
	}

	if (GetTotalMassOfActors() >= MassToOpen)
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}

}

void UOpenDoor::TestFuncFromC()
{
	UE_LOG(LogTemp, Warning, TEXT("this is cpp function."));

}

void UOpenDoor::OpenDoor()
{
	OnOpenDoorRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	OnCloseDoorRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOfActors()
{
	// 与 trigger 区域 重合的 数组
	TArray<AActor*> OverLappingActors;

	if (TriggerArea == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerArea is null."));
		return -1.0f;
	}

	TriggerArea->GetOverlappingActors(OverLappingActors);
	float TotalMass = 0.0f;
	for (auto OneActor : OverLappingActors)
	{
		TotalMass += OneActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

