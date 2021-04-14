// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExMmoController.generated.h"

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExMmoController : public APlayerController
{
	GENERATED_BODY()
	

public:

	//«–ªª ‰»Îƒ£ Ω
	void SwitchInputMode(bool IsShowUI);
};
