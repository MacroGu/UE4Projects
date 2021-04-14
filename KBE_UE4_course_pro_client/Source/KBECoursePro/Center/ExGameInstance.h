// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FText RoomName;

	
};
