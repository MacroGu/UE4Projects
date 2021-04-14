// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExBagBlock.generated.h"

class UExGoodItem;
class UOverlay;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExBagBlock : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void UpdateBlock();

	// 初始化格子类型于Id
	UFUNCTION(BlueprintCallable)
		void InitBlockInfo(EBagType InType, uint8 InId);

	// 是否允许放下物品
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void IsAllowDropDown(bool& DropResult);

	// 向服务器请求转移物品，同时创建出一个新的GoodItem添加到格子
	UFUNCTION(BlueprintCallable)
		void RequestPassGood();

	// 把物品放回原格子
	UFUNCTION(BlueprintCallable)
		void ReviseDragGood();

public:

	UPROPERTY(BlueprintReadOnly)
		EBagType BagType;

	UPROPERTY(BlueprintReadOnly)
		uint8 BlockId;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExGoodItem> GoodItemClass;

	UPROPERTY(BlueprintReadWrite)
		UExGoodItem* GoodItem;

	UPROPERTY(Meta = (BindWidget))
		UOverlay* RootBox;

};
