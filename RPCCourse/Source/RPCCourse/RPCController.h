// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPCController.generated.h"

/**
 * 
 */
UCLASS()
class RPCCOURSE_API ARPCController : public APlayerController
{
	GENERATED_BODY()


public:

	virtual void BeginPlay() override;
	
	void EchoNetMode();

};
