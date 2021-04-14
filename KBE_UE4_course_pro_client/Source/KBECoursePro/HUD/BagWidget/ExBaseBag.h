// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExBaseBag.generated.h"

class UExBagBlock;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExBaseBag : public UUserWidget
{
	GENERATED_BODY()
	
public:


	virtual void UpdateBlock(uint8 BlockId);


public:

	UPROPERTY(BlueprintReadWrite)
		TArray<UExBagBlock*> BlockGroup;


};
