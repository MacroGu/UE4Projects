// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExKbeGameMode.generated.h"

class UKBEventData;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExKbeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AExKbeGameMode();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void StartReloginBaseapp();

	void StopReloginBaseapp();

	// 绑定给定时器的事件
	void OnReloginBaseappTimer();

public:


protected:

	virtual void BeginPlay() override;

	// 注册KBE事件
	virtual void InstallEvent();

	// 注销KBE事件
	virtual void UnInstallEvent();

	void OnKicked(const UKBEventData* EventData);

	void OnDisconnected(const UKBEventData* EventData);

	void OnConnectionState(const UKBEventData* EventData);

	void OnReloginBaseappSuccessfully(const UKBEventData* EventData);

	void OnReloginBaseappFailed(const UKBEventData* EventData);

protected:

	FTimerHandle ReloginHandle;

};
