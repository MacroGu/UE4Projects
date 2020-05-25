// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest/QuestManager.h"
#include "QuestLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BLUEPRINTSTOCPP_API UQuestLibrary : public UObject
{
	GENERATED_BODY()


	static AQuestManager* GetQuestManager();


};
