// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExGoodItem.generated.h"

class UImage;
class UTextBlock;


// 从BagBlock移出委托
DECLARE_DELEGATE(FLeaveBagBlock)

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExGoodItem : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void InitGoodItem(EBagType InType, uint8 InId);

	// 是否允许拿起
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void IsAllowDragUp(bool& IsAllow);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		void AcceptDragUp(uint8& GoodId, uint8& Number);

	UFUNCTION(BlueprintCallable)
		void LeaveBagBlock();


public:

	UPROPERTY(Meta = (BindWidget))
		UImage* GoodImage;
	
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NumberText;

	// 保存背包类型和格子ID
	EBagType BagType;

	uint8 BlockId;

	// 委托通知所属的BagBlock自己已经被移出
	FLeaveBagBlock LeaveBagBlockDel;

};
