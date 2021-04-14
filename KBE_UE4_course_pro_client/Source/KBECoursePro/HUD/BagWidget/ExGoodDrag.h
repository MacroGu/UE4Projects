// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExGoodDrag.generated.h"


class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExGoodDrag : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable)
		void InitGoodInfo(uint8 GoodId, uint8 Number);

	UPROPERTY(Meta = (BindWidget))
		UImage* GoodImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NumberText;

};
