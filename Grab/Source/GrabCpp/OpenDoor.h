// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutputDeviceDebug.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

// second way of calling funtion from BP
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDoorRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseDoorRequest);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRABCPP_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Angle = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerArea = nullptr;
	
	UPROPERTY(EditAnywhere)
	float MassToOpen = 25.0f;

	UFUNCTION(BlueprintCallable, Category="MyOpenDoor")
	void TestFuncFromC();
	
	UPROPERTY(BlueprintAssignable)
	FOpenDoorRequest OnOpenDoorRequest;

	UPROPERTY(BlueprintAssignable)
	FCloseDoorRequest OnCloseDoorRequest;

private:
	void OpenDoor();
	void CloseDoor();

	float GetTotalMassOfActors();
};
