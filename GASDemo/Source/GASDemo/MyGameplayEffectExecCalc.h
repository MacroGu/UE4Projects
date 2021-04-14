// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MyGameplayEffectExecCalc.generated.h"




/**
 * 
 */
UCLASS()
class GASDEMO_API UMyGameplayEffectExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UMyGameplayEffectExecCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
