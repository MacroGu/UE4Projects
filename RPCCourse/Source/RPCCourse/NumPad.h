// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NumPad.generated.h"

class UTextRenderComponent;

UCLASS()
class RPCCOURSE_API ANumPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANumPad();

	void AssignRenderText(FString InText);


public:

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TextRender;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
