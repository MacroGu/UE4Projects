// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExGoodDrag.h"
#include "Image.h"
#include "TextBlock.h"


void UExGoodDrag::InitGoodInfo(uint8 GoodId, uint8 Number)
{
	GoodImage->SetBrushFromTexture((UTexture2D*)UExDataMgr::Get()->GetGoodTexture(GoodId));
	NumberText->SetText(FText::FromString(FString::FromInt(Number)));

	// 把自己保存到数据管理器
	UExDataMgr::Get()->GoodDrag = this;

}
