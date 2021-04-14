// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExLoginController.h"

void AExLoginController::BeginPlay()
{

	Super::BeginPlay();

	// 设置游戏窗口大小 r.setres 960*540w
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), ScreenWidth, ScreenHeight));

	bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

}
