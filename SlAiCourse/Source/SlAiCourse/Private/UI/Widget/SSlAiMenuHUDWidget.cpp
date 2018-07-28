// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"
#include "SImage.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SOverlay.h"
#include "Engine/Engine.h"
#include "SDPIScaler.h"
#include "SSlAiMenuWidget.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	// »ñÈ¡±à¼­Æ÷µÄMenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

	ChildSlot
		[
			SNew(SOverlay)
	+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(&MenuStyle->MenuHUDBackgroundBrush)
		]

	+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(MenuWidget, SSlAiMenuWidget)
		]

		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSlAiMenuHUDWidget::GetUIScaler() const
{
	return GetViewPortsize().Y / 1080.f;
}

FVector2D SSlAiMenuHUDWidget::GetViewPortsize() const
{
	FVector2D result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(result);
	}

	return result;
}

