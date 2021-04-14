// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayEffectExecCalc.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include <GameplayEffectTypes.h>

struct RPGDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Life);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxLife);

	RPGDamageStatics()
	{
		// Also capture the source's raw Damage, which is normally passed in directly via the execution
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MaxLife, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Life, Target, false);
	}

};

static const RPGDamageStatics& DamageStatics()
{
	static RPGDamageStatics DmgStatics;
	return DmgStatics;
}


UMyGameplayEffectExecCalc::UMyGameplayEffectExecCalc()
{
	this->RelevantAttributesToCapture.Add(DamageStatics().LifeDef);
	RelevantAttributesToCapture.Add(DamageStatics().MaxLifeDef);
}

void UMyGameplayEffectExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Life = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LifeDef, EvaluateParameters, Life);

	float MaxLife = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MaxLifeDef, EvaluateParameters, MaxLife);

	float DameageDone = 0.5 * Life;
	if (DameageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().LifeProperty, EGameplayModOp::Additive, -DameageDone));
	}

}
