// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/ExKbeGameMode.h"
#include "ExRoomGameMode.generated.h"


class UExRoomWidget;
class UKBEventData;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExRoomGameMode : public AExKbeGameMode
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExRoomWidget> RoomWidgetClass;

	UExRoomWidget* RoomWidget;

public:

	// 请求房间列表回调函数
	void OnReqRoomList(const UKBEventData* EventData);

	// 创建房价回调函数
	void OnCreateRoom(const UKBEventData* EventData);

	// 玩家进入游戏场景
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

protected:

	virtual void BeginPlay() override;

	virtual void InstallEvent() override;

	
};
