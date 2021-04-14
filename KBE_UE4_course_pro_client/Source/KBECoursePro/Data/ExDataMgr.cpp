// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ExDataMgr.h"
#include "Scripts/ExCommon.h"
#include "HUD/BagWidget/ExGoodDrag.h"


UExDataMgr* UExDataMgr::MgrInst = NULL;

UExDataMgr* UExDataMgr::Get()
{
	if (MgrInst == NULL)
	{
		MgrInst = NewObject<UExDataMgr>();
		MgrInst->AddToRoot();
		MgrInst->LoadTotalData();
	}
	return MgrInst;
}

void UExDataMgr::LoadTotalData()
{
	TotalData = LoadObject<UExDataAsset>(NULL, TEXT("ExDataAsset'/Game/Blueprint/Data/TotalData.TotalData'"));

	GoodDatas.Reset();

	GoodDatas.Add(0, FGoodData(EGoodType::Skill, 0));
	GoodDatas.Add(1, FGoodData(EGoodType::Skill, 1));
	GoodDatas.Add(2, FGoodData(EGoodType::Skill, 2));
	GoodDatas.Add(3, FGoodData(EGoodType::Buff, 0));
	GoodDatas.Add(4, FGoodData(EGoodType::Buff, 1));
	GoodDatas.Add(5, FGoodData(EGoodType::Buff, 2));
	GoodDatas.Add(6, FGoodData(EGoodType::Equip, 0));
	GoodDatas.Add(7, FGoodData(EGoodType::Equip, 1));
	GoodDatas.Add(8, FGoodData(EGoodType::Equip, 2));

}

UTexture* UExDataMgr::GetGoodTexture(int32 InIndex)
{
	return TotalData->GoodTextures[InIndex];
}

uint8 UExDataMgr::GetKindByGoodId(uint8 GoodId)
{
	return GoodDatas.Find(GoodId)->GoodKind;
}

EGoodType UExDataMgr::GetTypeByGoodId(uint8 GoodId)
{
	return GoodDatas.Find(GoodId)->GoodType;
}

void UExDataMgr::ChangeGoodInfo(EBagType BagType, FGoodInfo GoodInfo)
{
	if (GoodInfo.IsEmpty())
	{
		switch (BagType)
		{
		case EBagType::MainBag:
			MainBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::SkillBag:
			SkillBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::BuffBag:
			BuffBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::EquipBag:
			EquipBag.Remove(GoodInfo.BlockId);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (BagType)
		{
		case EBagType::MainBag:
			MainBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::SkillBag:
			SkillBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::BuffBag:
			BuffBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::EquipBag:
			EquipBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		default:
			break;
		}
	}

	UpdateBagBlockDel.ExecuteIfBound(BagType, GoodInfo.BlockId);
}

bool UExDataMgr::IsGoodExist(EBagType BagType, uint8 BlockId) const
{
	switch (BagType)
	{
	case EBagType::MainBag:
		return MainBag.Contains(BlockId);
		break;
	case EBagType::SkillBag:
		return SkillBag.Contains(BlockId);
		break;
	case EBagType::BuffBag:
		return BuffBag.Contains(BlockId);
		break;
	case EBagType::EquipBag:
		return EquipBag.Contains(BlockId);
		break;
	default:
		break;
	}

	return false;
}

const FGoodInfo UExDataMgr::GetGoodInfo(EBagType BagType, uint8 BlockId) const
{
	switch (BagType)
	{
	case EBagType::MainBag:
		return *MainBag.Find(BlockId);
	case EBagType::SkillBag:
		return *SkillBag.Find(BlockId);
	case EBagType::BuffBag:
		return *BuffBag.Find(BlockId);
	case EBagType::EquipBag:
		return *EquipBag.Find(BlockId);
	default:
		break;
	}

	// ...
	FGoodInfo tempGoodInfo;
	tempGoodInfo.InitInfo(0, 0, 0);
	return tempGoodInfo;

}

bool UExDataMgr::IsHandGoodExist()
{
	return GoodDrag != NULL;
}

FGoodInfo UExDataMgr::GetHandGoodInfo() const
{
	return GetGoodInfo(HandBagType, HandBlockId);
}

void UExDataMgr::ReviseHandGood()
{
	if (GoodDrag)
	{
		GoodDrag->RemoveFromParent();
	}

	GoodDrag = NULL;
	// 刷新格子的UI
	UpdateBagBlockDel.ExecuteIfBound(HandBagType, HandBlockId);
}

void FGoodInfo::InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber)
{
	BlockId = InBlockId;
	GoodId = InGoodId;
	Number = InNumber;
	GoodType = UExDataMgr::Get()->GetTypeByGoodId(GoodId);
	GoodKind = UExDataMgr::Get()->GetKindByGoodId(GoodId);
}
