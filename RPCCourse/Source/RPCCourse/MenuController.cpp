// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuController.h"
#include "MenuWidget.h"


void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	// 设定输入模式
	bShowMouseCursor = true;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	// 创建UI
	UClass* MenuWidgetClass = LoadClass<UMenuWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprint/MenuWidget_BP.MenuWidget_BP_C'"));
	UMenuWidget* MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
	MenuWidget->AddToViewport();

}
