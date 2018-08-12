// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandNone.h"
#include "SlAiHandAxe.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandAxe : public ASlAiHandNone
{
	GENERATED_BODY()
	
public:
	ASlAiHandAxe();

protected:
	virtual void BeginPlay() override;
	
	
};
