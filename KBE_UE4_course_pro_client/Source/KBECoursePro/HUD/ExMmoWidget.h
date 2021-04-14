// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Data/ExDataMgr.h"
#include "ExMmoWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UOverlay;
class UKBEventData;
class UExMainBag;
class UExEquipBag;
class UExSkillBag;
class UExBuffBag;
class UExChatRoom;
class AExPlayerCharacter;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExMmoWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	void InstallEvents(FText RoomName);

	void UnInstallEvents();

	void SetName(FString InName);

	void SetHpPercent(float InPercent);

	UFUNCTION(BlueprintCallable)
	void ReliveEvent();

	UFUNCTION(BlueprintCallable)
		void LeaveRoom();

	// 显示与关闭背包
	void OpenOrCloseBag(bool IsOpen);

	// 接受Drop事件后还原物品
	UFUNCTION(BlueprintCallable)
		void ReviseDragGood();

	void SetBaseHp(int32 InBaseHp);

	void SetDefense(int32 InDefense);

	void SetPowerRatio(float InPowerRatio);

	void SetSpeedRatio(float InSpeedRatio);

	// 检查一次哪个技能被激活
	void UpdateSkillOn();

public:

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RoomText;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* BloodProgress;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* ReliveBox;

	UPROPERTY(Meta = (BindWidget))
		UExMainBag* MainBag;

	UPROPERTY(Meta = (BindWidget))
		UExEquipBag* EquipBag;

	UPROPERTY(Meta = (BindWidget))
		UExSkillBag* SkillBag;

	UPROPERTY(Meta = (BindWidget))
		UExBuffBag* BuffBag;

	UPROPERTY(Meta = (BindWidget))
		UExChatRoom* ChatRoom;

	UPROPERTY()
		AExPlayerCharacter* PlayerCharacter;

protected: 

	void OnReqBagList(const UKBEventData* EventData);

	void UpdateBagBlock(EBagType BagType, uint8 BlockId);

	void OnPassGood(const UKBEventData* EventData);

	void OnReduceGood(const UKBEventData* EventData);

	void OnIncreaseGood(const UKBEventData* EventData);

};
