// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/ExEventData.h"
#include "ExRoomItem.generated.h"


class UImage;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FRoomItemSelect, uint64)

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExRoomItem : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable)
		void ItemButtonEvent();

	void InitItem(FROOM_INFO InRoomInfo);

	void ItemSelect();

	void UnItemSelect();


public:

	UPROPERTY(Meta = (BindWidget))
		UImage* OutLineImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY()
		FROOM_INFO RoomInfo;

	FRoomItemSelect RoomItemSelectDel;

	bool IsSelected;


};
