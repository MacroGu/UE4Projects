// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExKBEClient.generated.h"

class UKBEMain;


UCLASS()
class KBECOURSEPRO_API AExKBEClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExKBEClient();

public:

	UPROPERTY(EditAnywhere)
	UKBEMain* KBEMain;


};
