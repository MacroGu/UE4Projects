// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"


class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSlAiGameOptionWidget;
class SSlAiNewGameWidget;
class SSlAiChooseRecordWidget;

/**
 * 
 */
class SLAICOURSE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


private:
	// 绑定到各个MenuItem的方法
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	// 修改语言
	void ChangeCulture(ECultureTeam Culture);
	// 修改音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	// 初始化所有的控件
	void InitializeMenuList();
	// 选择显示的界面
	void ChooseWidget(EMenuType::Type WidgetType);
	// 修改菜单的大小
	void ResetWidgetSize(float NewWidth, float NewHeight);

private:

	// 保存根节点
	TSharedPtr<SBox> RootSizeBox;
	// 保存MenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	// 保存标题
	TSharedPtr<STextBlock> TitleText;
	// 用来保存垂直列表
	TSharedPtr<SVerticalBox> ContentBox;
	// 保存菜单组
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	// 游戏设置Widget 的指引
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	// 新游戏控件指针
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	// 选择存档控件指针
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;

};
