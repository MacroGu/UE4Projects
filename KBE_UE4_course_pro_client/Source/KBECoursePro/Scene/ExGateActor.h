// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ExActorEntity.h"
#include "ExGateActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UWidgetComponent;
class USceneComponent;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExGateActor : public AExActorEntity
{
	GENERATED_BODY()

public:

	AExGateActor();

	virtual void Tick(float DeltaSeconds) override;

public:

	int32 EntityId;

	uint64 RoomId;

	FString RoomName;


protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateRoomName(const FText& RoomName);

protected:

	UPROPERTY(EditAnywhere)
		USceneComponent* RootScene;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GateMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* GateBox;

	UPROPERTY(BlueprintReadWrite)
		UWidgetComponent* GateWidget;
	
};
