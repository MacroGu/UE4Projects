// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/ExKbeGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"



AExKbeGameMode::AExKbeGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AExKbeGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnInstallEvent();

}

void AExKbeGameMode::BeginPlay()
{
	Super::BeginPlay();
	InstallEvent();

}

void AExKbeGameMode::InstallEvent()
{
	// 注册最基本的回调事件
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);


}

void AExKbeGameMode::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();

}

void AExKbeGameMode::OnKicked(const UKBEventData* EventData)
{
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(EventData);

	DDH::Debug() << "OnKicked: failedcode --> " << ServerData->failedcode << "; errorstr -- > " << ServerData->errorStr << DDH::Endl();

}

void AExKbeGameMode::OnDisconnected(const UKBEventData* EventData)
{

	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(EventData);
	DDH::Debug() << "UKBEventData_onDisconnected: eventName --> " << ServerData->eventName << DDH::Endl();

}

void AExKbeGameMode::OnConnectionState(const UKBEventData* EventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(EventData);
	DDH::Debug() << "UKBEventData_onConnectionState: address --> " << ServerData->address << " success: " << ServerData->success << DDH::Endl();
}

void AExKbeGameMode::OnReloginBaseappSuccessfully(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(EventData);
	DDH::Debug() << "UKBEventData_onReloginBaseappSuccessfully, EventName:  " << ServerData->eventName << DDH::Endl();

	StopReloginBaseapp();

}

void AExKbeGameMode::OnReloginBaseappFailed(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(EventData);
	DDH::Debug() << "UKBEventData_onReloginBaseappFailed, failedcode:  " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AExKbeGameMode::StartReloginBaseapp()
{
	if (!ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AExKbeGameMode::OnReloginBaseappTimer, 1.f, true);

	}

}

void AExKbeGameMode::StopReloginBaseapp()
{
	if (ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
	}

}

void AExKbeGameMode::OnReloginBaseappTimer()
{
	// 断线重连事件
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();

}