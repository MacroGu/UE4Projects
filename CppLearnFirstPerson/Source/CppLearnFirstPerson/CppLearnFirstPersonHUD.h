// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CppLearnFirstPersonHUD.generated.h"

UCLASS()
class ACppLearnFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACppLearnFirstPersonHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

