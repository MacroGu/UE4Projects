// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/BagWidget/ExBaseBag.h"
#include "ExEquipBag.generated.h"

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExEquipBag : public UExBaseBag
{
	GENERATED_BODY()
	

public:

	virtual void UpdateBlock(uint8 BlockId) override;

	void SetBaseHp(int32 InBaseHp);

	void SetDefense(int32 InDefense);

	void SetPowerRatio(float InPowerRatio);

	void SetSpeedRatio(float InSpeedRatio);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeHelmet(bool IsOn);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeArmor(bool IsOn);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeShoes(bool IsOn);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeHpText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeDefenseText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangePowerText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeSpeedText(const FText& InText);

};
