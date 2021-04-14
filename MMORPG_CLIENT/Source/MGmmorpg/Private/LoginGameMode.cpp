// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Proto/scene.pb.h"
#include "Engine.h"




void ALoginGameMode::BeginPlay()
{
	bIsConnected = false;
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	ClientSocket::GetSingleton()->SetCurrentGameMode(this);
}

bool ALoginGameMode::Connect(const FText& ServerIp, const FText& ServerPort)
{
	ClientSocket::GetSingleton()->Init();
	ClientSocket::GetSingleton()->SetServerIPandPort(ServerIp.ToString(), FCString::Atoi(*ServerPort.ToString()));
	bIsConnected = ClientSocket::GetSingleton()->ConnectServer();
	if (bIsConnected)
	{
		return true;
	}

	return false;
}

bool ALoginGameMode::Login(const FText& username, const FText& Pw)
{
// 	if (username.IsEmpty() || Pw.IsEmpty())
// 		return false;
// 
// 	if (!bIsConnected)
// 		return false;

	return ClientSocket::GetSingleton()->Login(username, Pw);

}

bool ALoginGameMode::SignUp(const FText& username, const FText& Pw)
{
	return ClientSocket::GetSingleton()->SignUp(username, Pw);

	if (username.IsEmpty() || Pw.IsEmpty())
		return false;

	if (!bIsConnected)
		return false;

}

void ALoginGameMode::EnterScene()
{
	if (HUDWidgetClass && CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		UGameplayStatics::OpenLevel(this, "MainScene");
	}
}
