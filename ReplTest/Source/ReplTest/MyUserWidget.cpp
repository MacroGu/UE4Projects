// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "ReplTestPlayerController.h"


UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TxtUsername = NULL;
	TxtServerIP = NULL;
	TxtServerPort = NULL;
	BtnLogin = NULL;
}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UEditableTextBox* txtbox = Cast<UEditableTextBox>(GetWidgetFromName("TxtboxUsername")))
	{
		TxtUsername = txtbox;
	}

	if (UEditableTextBox* txtbox = Cast<UEditableTextBox>(GetWidgetFromName("TxtboxServerIP")))
	{
		TxtServerIP = txtbox;
	}

	if (UEditableTextBox* txtbox = Cast<UEditableTextBox>(GetWidgetFromName("TxtboxServerPort")))
	{
		TxtServerPort = txtbox;
	}

	if (UButton* btn = Cast<UButton>(GetWidgetFromName("BtnLogin")))
	{
		BtnLogin = btn;

		FScriptDelegate Del;
		Del.BindUFunction(this, "OnBtnLoginClick");
		btn->OnClicked.Add(Del);
	}
}

void UMyUserWidget::OnBtnLoginClick()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		FString URL = FString::Printf(TEXT("%s:%s?Alias=%s"), *(TxtServerIP->GetText().ToString()), *(TxtServerPort->GetText().ToString()), *(TxtUsername->GetText().ToString()));
		PC->ClientTravel(*URL, TRAVEL_Absolute);
	}
}
