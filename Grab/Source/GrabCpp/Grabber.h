// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Public/DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Public/CollisionQueryParams.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRABCPP_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 射线长度
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;
	

	// 输入组件
	UInputComponent* InputComponent = nullptr;
	// 物理握把组件  ？？？
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	FVector GetLineStartPos();
	FVector GetLineEndPos();
	FVector GetOriginPos();

	FHitResult GetFirstPhysicsBodyInReach();

	void SetPhysicsHandleComponent();
	void SetInputComponent();

	void Grab();
	void Release();

	float originDistance = 0.0f;

};
