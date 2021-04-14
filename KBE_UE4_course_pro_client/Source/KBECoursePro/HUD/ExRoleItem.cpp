// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExRoleItem.h"
#include "Image.h"
#include "TextBlock.h"
#include "Scripts/ExEventData.h"





void UExRoleItem::ItemButtonEvent()
{
	RoleItemSelectDel.ExecuteIfBound(RoleInfo.Dbid);


}

void UExRoleItem::InitItem(FROLE_INFO InRoleInfo)
{
	RoleInfo = InRoleInfo;
	ItemName->SetText(FText::FromString(RoleInfo.Name));
	// 如果该角色是上次游戏退出时选中的， 就设置选定该条目
	if (RoleInfo.IsLastRole)
	{
		RoleItemSelectDel.ExecuteIfBound(RoleInfo.Dbid);
	}
}

void UExRoleItem::ItemSelect()
{
	RoleInfo.IsLastRole = true;
	OutLineImage->SetVisibility(ESlateVisibility::Visible);
}

void UExRoleItem::UnItemSelect()
{
	RoleInfo.IsLastRole = false;
	OutLineImage->SetVisibility(ESlateVisibility::Hidden);
}
