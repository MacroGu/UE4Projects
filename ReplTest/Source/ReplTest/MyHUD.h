// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class REPLTEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AMyHUD();

	virtual void PostInitializeComponents() override;

	virtual void DrawHUD() override;
	
private:

	void DrawRoleAlias();

	UFont* Font;
};
