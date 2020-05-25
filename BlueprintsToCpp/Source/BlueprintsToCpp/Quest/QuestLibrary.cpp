// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLibrary.h"
#include "Kismet/GameplayStatics.h"


AQuestManager* UQuestLibrary::GetQuestManager()
{
	auto game_mode = UGameplayStatics::GetGameMode();
	if (!game_mode)
	{
		return nullptr;
	}




}
