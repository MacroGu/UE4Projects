// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"





ASlAiPlayerController::ASlAiPlayerController()
{
	// 允许每一帧允许
	PrimaryActorTick.bCanEverTick = true;

}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// 获取角色
	if (!SPCharacter)
	{
		SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());
	}

	// 设置鼠标不显示
	bShowMouseCursor = false;
	// 设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	// 100
	// 龙潭路218
}

void ASlAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 绑定视角切换
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASlAiPlayerController::ChangeView);
	// 绑定鼠标按下事件
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASlAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASlAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASlAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASlAiPlayerController::RightEventStop);

}

void ASlAiPlayerController::ChangeView()
{
	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;

	case  EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;

	default:
		break;
	}
}

void ASlAiPlayerController::LeftEventStart()
{

}

void ASlAiPlayerController::LeftEventStop()
{

}

void ASlAiPlayerController::RightEventStart()
{

}

void ASlAiPlayerController::RightEventStop()
{

}
