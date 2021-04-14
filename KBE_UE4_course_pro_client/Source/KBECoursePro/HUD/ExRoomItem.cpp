// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExRoomItem.h"
#include "TextBlock.h"
#include "Image.h"



void UExRoomItem::ItemButtonEvent()
{
	RoomItemSelectDel.ExecuteIfBound(RoomInfo.RoomId);
}

void UExRoomItem::InitItem(FROOM_INFO InRoomInfo)
{
	RoomInfo = InRoomInfo;
	ItemName->SetText(FText::FromString(RoomInfo.Name));
}

void UExRoomItem::ItemSelect()
{
	IsSelected = true;
	OutLineImage->SetVisibility(ESlateVisibility::Visible);
}

void UExRoomItem::UnItemSelect()
{
	IsSelected = false;
	OutLineImage->SetVisibility(ESlateVisibility::Hidden);
}
