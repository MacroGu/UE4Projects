// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateFontInfo.h"
#include "SlateBrush.h"

#include "SlAiGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAICOURSE_API FSlAiGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiGameStyle();
	virtual ~FSlAiGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiGameStyle& GetDefault();

	// 指定快捷栏的容器图标， 把快捷栏的style 指定到package
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush NormalContainerBrush;

	// 指定被选择的容器Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ChoosedContainerBrush;

	// 指定没有颜色的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush EmptyBrush;


	/*
	60 号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;

	/*
	40 号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;
	/*
	30 号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	/*
	20 号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_20;

	// 16 号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_16;
	// 20 号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_20;
	// 40 号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_40;
	// 50 号字体有轮廓
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_50;


	// 黑色颜色
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;

	// 白色颜色
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
