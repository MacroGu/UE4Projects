// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExBagBlock.h"
#include "Overlay.h"
#include "OverlaySlot.h"
#include "ExGoodItem.h"
#include "ExGoodDrag.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"


void UExBagBlock::UpdateBlock()
{
	// 从ExDataMgr 获取该格子对应的物品信息
	if (!UExDataMgr::Get()->IsGoodExist(BagType, BlockId))
	{
		if (GoodItem)
		{
			GoodItem->RemoveFromParent();
			GoodItem = NULL;
		}
	}
	else
	{
		const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);
		// 如果GoodItem 不存在
		if (!GoodItem)
		{
			GoodItem = CreateWidget<UExGoodItem>(this, GoodItemClass);
			UOverlaySlot* ItemSlot = RootBox->AddChildToOverlay(GoodItem);
			ItemSlot->SetHorizontalAlignment(HAlign_Center);
			ItemSlot->SetVerticalAlignment(VAlign_Center);

			// 绑定委托
			GoodItem->LeaveBagBlockDel.BindLambda([this]() {
				GoodItem = NULL;
				});

		}
		//  添加数据给GoodItem
		GoodItem->InitGoodItem(BagType, BlockId);
	}
}

void UExBagBlock::InitBlockInfo(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;
}

void UExBagBlock::IsAllowDropDown(bool& DropResult)
{
	DropResult = false;

	// 判断框里是否有物品
	if (GoodItem)
	{
		return;
	}

	// 是否是原格子
	if (UExDataMgr::Get()->HandBagType == BagType && UExDataMgr::Get()->HandBlockId == BlockId)
	{
		return;
	}

	const FGoodInfo HandGoodInfo = UExDataMgr::Get()->GetHandGoodInfo();

	// 判断是否匹配
	switch (BagType)
	{
	case EBagType::MainBag:
		DropResult = true;
		break;
	case EBagType::SkillBag:
		if (HandGoodInfo.GoodType == EGoodType::Skill)
		{
			DropResult = true;
		}
		break;
	case EBagType::BuffBag:
		if (HandGoodInfo.GoodType == EGoodType::Buff)
		{
			DropResult = true;
		}
		break;
	case EBagType::EquipBag:
		if (HandGoodInfo.GoodType == EGoodType::Equip)
		{
			// 装备需要判断格子ID
			if (HandGoodInfo.GoodKind == BlockId)
			{
				DropResult = true;
			}
		}
		break;
	default:
		break;
	}
}

void UExBagBlock::RequestPassGood()
{
	// 向服务器申请移动物品
	UKBEventData_PassGood* EventData = NewObject<UKBEventData_PassGood>();
	EventData->ArcBagType = (uint8)UExDataMgr::Get()->HandBagType;
	EventData->ArcBlockId = UExDataMgr::Get()->HandBlockId;
	EventData->DesBagType = (uint8)BagType;
	EventData->DesBlockId = BlockId;
	KBENGINE_EVENT_FIRE("PassGood", EventData);

	// 清空拖拽的物品信息
	if (UExDataMgr::Get()->GoodDrag)
	{
		UExDataMgr::Get()->GoodDrag->RemoveFromParent();
	}
	UExDataMgr::Get()->GoodDrag = NULL;

	// 创建空的物品信息和空的格子数据, 给移出物品格子使用
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(UExDataMgr::Get()->HandBlockId, 0, 0);

	// 当前格子更新的物品的信息
	FGoodInfo DesGoodInfo = UExDataMgr::Get()->GetHandGoodInfo();
	// 修改格子id
	DesGoodInfo.BlockId = BlockId;

	// 交换格子数据
	UExDataMgr::Get()->ChangeGoodInfo(UExDataMgr::Get()->HandBagType, ArcGoodInfo);
	UExDataMgr::Get()->ChangeGoodInfo(BagType, DesGoodInfo);
}

void UExBagBlock::ReviseDragGood()
{
	UExDataMgr::Get()->ReviseHandGood();
}
