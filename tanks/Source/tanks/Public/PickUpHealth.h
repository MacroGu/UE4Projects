// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "PickUpHealth.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API APickUpHealth : public APickUpBase
{
	GENERATED_BODY()

public:
	virtual void UseItem(AActor* User) override;
	
	UPROPERTY(EditAnyWhere, Category = "PickUp")
	float HealtToAdd = 20.0f;
};
