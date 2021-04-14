// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExDataAsset.h"
#include "ExDataMgr.generated.h"

class UExGoodDrag;

UENUM()
enum class EBagType : uint8
{
	MainBag = 0,
	SkillBag,
	BuffBag,
	EquipBag
};

UENUM()
enum class EGoodType : uint8
{
	Skill = 0,
	Buff,
	Equip
};

USTRUCT()
struct FGoodInfo
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 BlockId;

	UPROPERTY()
		uint8 GoodId;

	UPROPERTY()
		EGoodType GoodType;

	UPROPERTY()
		uint8 GoodKind;

	UPROPERTY()
		uint8 Number;

	FGoodInfo() {}

	void InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber);

	bool IsEmpty() const {
		return Number == 0;
	}

};

struct FGoodData
{
	EGoodType GoodType;

	uint8 GoodKind;

	FGoodData(EGoodType InType, uint8 InKind) : GoodType(InType), GoodKind(InKind) {}

};


// 更新背包物品请求刷新UI的 委托
DECLARE_DELEGATE_TwoParams(FUpdateBagBlock, EBagType, uint8)

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExDataMgr : public UObject
{
	GENERATED_BODY()
	

public:

	static UExDataMgr* Get();

	void LoadTotalData();

	// 获取数据函数
	UTexture* GetGoodTexture(int32 InIndex);

	uint8 GetKindByGoodId(uint8 GoodId);

	EGoodType GetTypeByGoodId(uint8 GoodId);

	void ChangeGoodInfo(EBagType BagType, FGoodInfo GoodInfo);

	bool IsGoodExist(EBagType BagType, uint8 BlockId) const;

	const FGoodInfo GetGoodInfo(EBagType BagType, uint8 BlockId) const;

	// 手上是否有物品
	bool IsHandGoodExist();

	// 手上是否有物品，并且返回物品信息
	FGoodInfo GetHandGoodInfo() const;

	// 请求将手上物品放置回拖拽处
	void ReviseHandGood();


public:

	UPROPERTY()
		TMap<uint8, FGoodInfo> SkillBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> BuffBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> EquipBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> MainBag;

	// 物品资料表 key 物品id
	TMap<uint8, FGoodData> GoodDatas;

	FUpdateBagBlock UpdateBagBlockDel;

	// 保存当前手上拿着的物品背包类型
	EBagType HandBagType;

	// 保存当前手术拿着的物品格子ID
	uint8 HandBlockId;

	// 保存跟随鼠标移动的物品UI，可以用于判断手上是否有物品
	UPROPERTY()
		UExGoodDrag* GoodDrag;

	uint8 CurrentOnSkill;

protected:

	UPROPERTY()
		UExDataAsset* TotalData;

	static UExDataMgr* MgrInst;
};
