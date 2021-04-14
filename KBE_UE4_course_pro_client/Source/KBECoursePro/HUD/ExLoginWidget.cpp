// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExLoginWidget.h"
#include "EditableTextBox.h"
#include "Center/ExLoginGameMode.h"
#include "Engine/KBEMain.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"
#include "Components/EditableTextBox.h"



void UExLoginWidget::InitWidget()
{
	clientVersionLabel->SetText(FText::FromString("client version:" + UKBEMain::getClientVersion()));
	clientScriptVersionLabel->SetText(FText::FromString("client script version:" + UKBEMain::getClientScriptVersion()));
	serverVersionLabel->SetText(FText::FromString("server version:" + UKBEMain::getServerVersion()));
	serverScriptVersionLabel->SetText(FText::FromString("server script version:" + UKBEMain::getServerScriptVersion()));
}

void UExLoginWidget::LoginButtonEvent()
{
	FString UserName = UserNameBox->GetText().ToString();
	FString PassWard = PasswardBox->GetText().ToString();
	if (UserName.IsEmpty() || PassWard.IsEmpty())
	{
		DDH::Debug() << "LoginButtonEvent user name or password can not be none " << DDH::Endl();
		return;
	}

	TArray<uint8> LoginData;
	FString ProjectName("KBECoursePro");

	for (int i = 0; i < ProjectName.Len(); ++i)
	{
		LoginData.Push((uint8)ProjectName[i]);
	}

	LoginGameMode->KBEMain->login(UserName, PassWard, LoginData);

}

void UExLoginWidget::RegisterButtonEvent()
{
	FString UserName = UserNameBox->GetText().ToString();
	FString PassWord = PasswardBox->GetText().ToString();
	if (UserName.IsEmpty() || PassWord.IsEmpty())
	{
		DDH::Debug() << "RegisterButtonEvent user name or password can not be none " << DDH::Endl();
		return;
	}

	TArray<uint8> AccountData;
	FString ProjectName("KBECoursePro");

	for (int i = 0; i < ProjectName.Len(); ++i)
	{
		AccountData.Add((uint8)ProjectName[i]);
	}

	LoginGameMode->KBEMain->createAccount(UserName, PassWord, AccountData);

}
