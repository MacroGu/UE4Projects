// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class URPCInstance;

/**
 * 
 */
UCLASS()
class RPCCOURSE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void AssignRPCInstance(URPCInstance* InInstance);

	UFUNCTION(BlueprintCallable)
	void LANServerEvent();

	UFUNCTION(BlueprintCallable)
	void LANClientEvent();


public:

	URPCInstance* RPCInstance;

};
