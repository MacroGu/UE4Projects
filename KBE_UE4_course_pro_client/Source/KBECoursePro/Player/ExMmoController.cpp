// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExMmoController.h"

void AExMmoController::SwitchInputMode(bool IsShowUI)
{
	if (IsShowUI)
	{
		bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
	else
	{
		bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		SetInputMode(InputMode);

	}
}
