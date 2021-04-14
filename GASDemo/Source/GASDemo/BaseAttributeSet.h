// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class GASDEMO_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UBaseAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxLife;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
