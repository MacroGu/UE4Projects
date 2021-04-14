// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include <GameplayEffectExtension.h>
#include "GameplayEffectTypes.h"
#include <Math/UnrealMathUtility.h>



UBaseAttributeSet::UBaseAttributeSet() : Life(100.f), MaxLife(100.f)
{
	
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	UProperty* updateProperty = Data.EvaluatedData.Attribute.GetUProperty();
	UProperty* checkProperty = FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Life));

	if (updateProperty == checkProperty)
	{
		Life.SetCurrentValue(FMath::Clamp<float>(Life.GetCurrentValue(), 0, MaxLife.GetCurrentValue()));
	}


}
