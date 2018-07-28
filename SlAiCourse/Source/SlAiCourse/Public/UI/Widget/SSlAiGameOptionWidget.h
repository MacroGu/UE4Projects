// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"

class SCheckBox;
class SSlider;
class STextBlock;

// 修改中英文委托
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
// 修改音量的委托
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

/**
 * 
 */
class SLAICOURSE_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}

	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	// 统一设置样式
	void StyleInitialize();
	// 中文 CheckBox 事件
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	// 英文 CheckBox 事件
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
	// 音量变化事件
	void MusicSliderChanged(float Value);
	void SoundSliderChanged(float Value);


private:
	// 获取 MenuStyle
	const struct FSlAiMenuStyle *MenuStyle;
	// 获取CheckBox指针
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
	// 两个进度条
	TSharedPtr<SSlider> MuSlider;	// 背景音乐
	TSharedPtr<SSlider> SoSlider;	// 音效
	// 进度条百分比
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;

	// 委托变量
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;

};
