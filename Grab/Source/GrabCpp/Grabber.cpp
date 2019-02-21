// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetInputComponent();
	SetPhysicsHandleComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle != nullptr)
	{
		PhysicsHandle->SetTargetLocation(GetOriginPos());
	}
}

FVector UGrabber::GetLineStartPos()
{
	FVector PlayViewerPointLocation;
	FRotator PlayViewerPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayViewerPointLocation, PlayViewerPointRotation);

	return PlayViewerPointLocation;
}

FVector UGrabber::GetLineEndPos()
{
	FVector PlayViewerPointLocation;
	FRotator PlayViewerPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayViewerPointLocation, PlayViewerPointRotation);

	FVector PlayViewerPointEndPoint = PlayViewerPointLocation + PlayViewerPointRotation.Vector() * Reach;

	return PlayViewerPointEndPoint;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/*
	DrawDebugLine(
		GetWorld(),
		GetLineStartPos(),
		GetLineEndPos(),
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);
	*/

	FCollisionQueryParams QueryParamter = FCollisionQueryParams("", false, GetOwner());

	FHitResult HitResult;			// 人物发出的射线 经过的物体
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetLineStartPos(),
		GetLineEndPos(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),		// 用于区别被阻挡的物体的类别
		QueryParamter
	);

	return HitResult;
}

void UGrabber::SetPhysicsHandleComponent()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not found"));
	}

}

void UGrabber::SetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found"));
	}
	else
	{
		// 绑定按键事件
		InputComponent->BindAction("GrabAction", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("GrabAction", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab mouse left button"));

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	
	if (ComponentToGrab == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ComponentToGrab is null"));
		return;
	}
	
	originDistance = HitResult.Distance;

	if (HitResult.GetActor() != nullptr && PhysicsHandle != nullptr)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			HitResult.GetActor()->GetActorLocation(),
			HitResult.GetActor()->GetActorRotation()
		);
	}

}

void UGrabber::Release()
{
	if (PhysicsHandle != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}

	UE_LOG(LogTemp, Warning, TEXT("Release mouse left button"));
}

FVector UGrabber::GetOriginPos()
{

	FVector PlayViewerPointLocation;
	FRotator PlayViewerPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayViewerPointLocation, PlayViewerPointRotation);

	FVector PlayViewerPointEndPoint = PlayViewerPointLocation + PlayViewerPointRotation.Vector() * originDistance;

	return PlayViewerPointEndPoint;
}

