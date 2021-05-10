// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class UEditableTextBox;
class UButton;

/**
 * 
 */
UCLASS()
class REPLTEST_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnBtnLoginClick();

private:

	UEditableTextBox* TxtUsername;
	UEditableTextBox* TxtServerIP;
	UEditableTextBox* TxtServerPort;
	UButton* BtnLogin;
	
};
