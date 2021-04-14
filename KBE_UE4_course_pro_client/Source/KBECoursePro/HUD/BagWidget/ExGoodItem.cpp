// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExGoodItem.h"
#include "Image.h"
#include "TextBlock.h"


void UExGoodItem::InitGoodItem(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;

	// 更新UI
	const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);
	NumberText->SetText(FText::FromString(FString::FromInt(GoodInfo.Number)));
	GoodImage->SetBrushFromTexture((UTexture2D*)UExDataMgr::Get()->GetGoodTexture(GoodInfo.GoodId));

}

void UExGoodItem::IsAllowDragUp(bool& IsAllow)
{
	// 判断当前是否有物品在拖拽
	if (UExDataMgr::Get()->IsHandGoodExist())
	{
		IsAllow = false;
		return;
	}

	IsAllow = true;
}

void UExGoodItem::AcceptDragUp(uint8& GoodId, uint8& Number)
{
	// 获取物品信息
	const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);

	// 保存拖拽信息到管理器
	UExDataMgr::Get()->HandBagType = BagType;
	UExDataMgr::Get()->HandBlockId = BlockId;

	// 返回数据给蓝图
	GoodId = GoodInfo.GoodId;
	Number = GoodInfo.Number;

}

void UExGoodItem::LeaveBagBlock()
{
	// 调用委托告诉所属格子自己被移出
	LeaveBagBlockDel.ExecuteIfBound();
	RemoveFromParent();
}
