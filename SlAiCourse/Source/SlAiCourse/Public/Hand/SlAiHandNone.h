// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandNone.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandNone : public ASlAiHandObject
{
	GENERATED_BODY()
	

public:
	ASlAiHandNone();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
