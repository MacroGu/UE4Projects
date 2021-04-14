// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExChatItem.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExChatItem : public UUserWidget
{
	GENERATED_BODY()
	

public:

	// 初始化数据
	void InitItem(FString Name, FString Date, FString Message);


public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* UserText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* InfoText;

};
