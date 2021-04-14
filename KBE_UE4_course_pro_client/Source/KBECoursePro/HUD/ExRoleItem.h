// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/ExEventData.h"
#include "ExRoleItem.generated.h"

class UImage;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FRoleItemSelect, uint64)


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExRoleItem : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void ItemButtonEvent();

	void InitItem(FROLE_INFO InRoleInfo);

	void ItemSelect();

	void UnItemSelect();


public:

	UPROPERTY(Meta = (BindWidget))
		UImage* OutLineImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY()
		FROLE_INFO RoleInfo;

	FRoleItemSelect RoleItemSelectDel;

};
