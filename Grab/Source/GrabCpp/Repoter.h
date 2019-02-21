// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Repoter.generated.h"








UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRABCPP_API URepoter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URepoter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
