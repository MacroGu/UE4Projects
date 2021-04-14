// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/ExKbeGameMode.h"
#include "ExMmoGameMode.generated.h"

class AExCharacterEntity;
class AExPlayerCharacter;
class AExRemoteCharacter;
class AExMonsterCharacter;
class AExSkillActor;
class AExFlobActor;
class UExMmoWidget;
class AExGateActor;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExMmoGameMode : public AExKbeGameMode
{
	GENERATED_BODY()


public:

	UPROPERTY()
		AExPlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AExPlayerCharacter>> PlayerClassList;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AExRemoteCharacter>> RemoteClassList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AExMonsterCharacter> MonsterClass;


	// 保持所有远程玩家和怪物
	UPROPERTY(EditAnywhere)
		TMap<int32, AExCharacterEntity*> CharacterMap;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExMmoWidget> MmoWidgetClass;

	UPROPERTY(EditAnywhere)
		TMap<int32, AExSkillActor*> SkillMap;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AExSkillActor>> SkillClassList;

	UPROPERTY(EditAnywhere)
		TMap<int32, AExFlobActor*> FlobMap;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AExFlobActor> FlobClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AExGateActor> GateClass;

	// 保存传送门
	UPROPERTY(EditAnywhere)
		AExGateActor* GateActor;

protected:

	virtual void InstallEvent() override;

	virtual void BeginPlay() override;

	void OnEnterWorld(const UKBEventData* EventData);

	void OnEnterSpace(const UKBEventData* EventData);

	void OnLeaveWorld(const UKBEventData* EventData);

	void OnLeaveSpace(const UKBEventData* EventData);

	void SetPosition(const UKBEventData* EventData);

	void SetDirection(const UKBEventData* EventData);

	void UpdatePosition(const UKBEventData* EventData);

	void OnAnimUpdate(const UKBEventData* EventData);

	void SetBaseHP(const UKBEventData* EventData);

	void SetHP(const UKBEventData* EventData);

	void SetDefense(const UKBEventData* EventData);

	void SetPowerRatio(const UKBEventData* EventData);

	void SetSpeedRatio(const UKBEventData* EventData);

	void OnAttack(const UKBEventData* EventData);

	// 离开房间返回大厅
	void OnLeaveRoom(const UKBEventData* EventData);

	// 玩家进入游戏场景
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

protected:

	UExMmoWidget* MmoWidget;


public:

	virtual void UnInstallEvent() override;


};
