// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));


}


void UGrabber::Grab()
{
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	if (TraceForPhysicsBodies(HitActor, HitComponent))
	{
		HitComponent->SetSimulatePhysics(true);
		GetPhysicsComponent()->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitComponent->GetCenterOfMass(),
			FRotator()
		);
		NotifyQuestActor(HitActor);
	}
}

void UGrabber::Release()
{
	GetPhysicsComponent()->ReleaseComponent();
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber BeginPlay"));

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetPhysicsComponent()->SetTargetLocationAndRotation(GetHoldLocation(), K2_GetComponentRotation());

}

FVector UGrabber::GetMaxGrabLocation() const
{
	
	return GetComponentLocation() + GetComponentRotation().Vector() * MaxGrabDistance;

}

FVector UGrabber::GetHoldLocation() const
{

	return GetComponentLocation() + GetComponentRotation().Vector() * HoldDistance;

}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::NotifyQuestActor(AActor* Actor)
{
	if (!Actor)
	{
		return;
	}


}

bool UGrabber::TraceForPhysicsBodies(AActor*& HitActor, UPrimitiveComponent*& HitComponent)
{
	FHitResult hit_result;
	TArray <TEnumAsByte <EObjectTypeQuery >> TraceObjectTypes;
	TArray <AActor*> IgnoreActors;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), K2_GetComponentLocation(), GetMaxGrabLocation(), GrabRadius,
		TraceObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, hit_result, true))
	{

		HitActor = hit_result.GetActor();
		HitComponent = hit_result.GetComponent();

		return true;
	}

	return false;
}
