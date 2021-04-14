// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/BagWidget/ExBaseBag.h"
#include "ExSkillBag.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExSkillBag : public UExBaseBag
{
	GENERATED_BODY()
	
public:

	void UpdateSkillOn();

	UPROPERTY(BlueprintReadWrite)
		TArray<UTextBlock*> OnTextGroup;

};
