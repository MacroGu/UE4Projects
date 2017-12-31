// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorActor.generated.h"

UCLASS()
class CPPLEARNFIRSTPERSON_API ARotatorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Multiplier;
	
};
