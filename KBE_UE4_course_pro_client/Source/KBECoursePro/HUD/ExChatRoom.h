// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExChatRoom.generated.h"


class USizeBox;
class UScrollBox;
class UEditableText;
class UExChatItem;
class UKBEventData;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExChatRoom : public UUserWidget
{
	GENERATED_BODY()
	
public:


	// 由MmoWidget触发注册事件
	void InstallEvent();

	// 注销事件
	void UnInstallEvents();

	// 显示隐藏输入框
	void ShowOrHideInput(bool IsShow);

	UFUNCTION(BlueprintCallable)
		void SendChatInfo();

	void AcceptChatList(const UKBEventData* EventData);

public:

	UPROPERTY(Meta = (BindWidget))
		USizeBox* ChatInputBox;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ChatScrollBox;

	UPROPERTY(Meta = (BindWidget))
		UEditableText* InputTextBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExChatItem> ChatItemClass;


};
