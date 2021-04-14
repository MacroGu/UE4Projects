// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExSkillBag.h"
#include "TextBlock.h"
#include "Data/ExDataMgr.h"


void UExSkillBag::UpdateSkillOn()
{
	for (int i = 0; i < OnTextGroup.Num(); ++i)
	{
		if (i == UExDataMgr::Get()->CurrentOnSkill)
		{
			OnTextGroup[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			OnTextGroup[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
