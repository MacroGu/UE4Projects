// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateBrush.h"
#include "SlateFontInfo.h"
#include "NoExportTypes.h"
#include "SlateSound.h"
#include "SlateTypes.h"
#include "SlAiMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAICOURSE_API FSlAiMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiMenuStyle();
	virtual ~FSlAiMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = MenuHUD)
	FSlateBrush MenuHUDBackgroundBrush;

	/*
		指定 Menu 的背景图片
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush MenuBackgroundBrush;

	/*
		Menu 左图标的 Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush LeftIconBrush;

	/*
		Menu 右图标的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush RightIconBrush;

	/*
		Menu 标题Border的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush TitleBorderBrush;

	/*
		MenuItem 的 Brush
	*/
	UPROPERTY(EditAnywhere, Category = MenuItem)
	FSlateBrush MenuItemBrush;

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

	// 黑色颜色
	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_Black;

	// 白色颜色
	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_White;

	// GameSet 的背景
	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush GameOptionBGBrush;

	// CheckBox 的 Brush 被选中
	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush CheckedBoxBrush;

	// CheckBox 的 Brush 不被选中
	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush UnCheckedBoxBrush;

	// Slider 的背景Brush
	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush SliderBarBrush;

	// 指定 Slider 的样式
	UPROPERTY(EditAnywhere, Category = GameOption)
	FSliderStyle SliderStyle;

	// 开始游戏声音
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound StartGameSound;

	// 结束游戏声音
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound ExitGameSound;

	// 转换按钮声音
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound MenuItemChangeSound;
	
	// Menu 背景声音
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound MenuBackGroundMusic;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
