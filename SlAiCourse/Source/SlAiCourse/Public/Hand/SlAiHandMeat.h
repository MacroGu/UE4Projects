// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandMeat.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandMeat : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandMeat();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
