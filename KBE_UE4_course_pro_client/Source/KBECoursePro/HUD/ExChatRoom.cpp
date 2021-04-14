// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExChatRoom.h"
#include "Scripts/ExEventData.h"
#include "ExChatItem.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/ScrollBoxSlot.h"




void UExChatRoom::InstallEvent()
{
	// 绑定远程回调方法， 注册了的事件在关卡销毁时一定要注销
	KBENGINE_REGISTER_EVENT("AcceptChatList", AcceptChatList);
}

void UExChatRoom::UnInstallEvents()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void UExChatRoom::ShowOrHideInput(bool IsShow)
{
	if (IsShow)
	{
		ChatInputBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ChatInputBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UExChatRoom::SendChatInfo()
{
	// 获取输入字符并清空输入框
	FString Message = InputTextBox->GetText().ToString();
	InputTextBox->SetText(FText());

	// 如果输入字符不为空， 发送
	if (!Message.IsEmpty())
	{
		UKBEventData_SendChatInfo* EventData = NewObject<UKBEventData_SendChatInfo>();
		EventData->Message = Message;
		KBENGINE_EVENT_FIRE("SendChatInfo", EventData);
	}

}

void UExChatRoom::AcceptChatList(const UKBEventData* EventData)
{
	const UKBEventData_AcceptChatList* ServerData = Cast<UKBEventData_AcceptChatList>(EventData);

	// 遍历生成新的ChatItem填充到ScrollBox
	for (auto Info : ServerData->ChatList)
	{
		UExChatItem* ChatItem = CreateWidget<UExChatItem>(this, ChatItemClass);
		ChatItem->InitItem(Info.Name, Info.Date, Info.Message);

		UScrollBoxSlot* ItemSlot = Cast<UScrollBoxSlot>(ChatScrollBox->AddChild(ChatItem));
		ItemSlot->SetHorizontalAlignment(HAlign_Fill);
		ItemSlot->SetVerticalAlignment(VAlign_Bottom);
		ItemSlot->SetPadding(FMargin(0.f, 20.f, 0.f, 0.f));

	}

	// 移动滚动栏到最低部
	ChatScrollBox->ScrollToEnd();

}
