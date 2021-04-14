/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class ExRole : public ExRoleBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "EntityCallExRoleBase.h"

namespace KBEngine
{

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/ExRole.def
	// Please inherit and implement "class ExRole : public ExRoleBase"
class KBENGINEPLUGINS_API ExRoleBase : public Entity
{
public:
	EntityBaseEntityCall_ExRoleBase* pBaseEntityCall;
	EntityCellEntityCall_ExRoleBase* pCellEntityCall;

	int32 BaseHP;
	virtual void onBaseHPChanged(int32 oldValue) {}
	int32 Defense;
	virtual void onDefenseChanged(int32 oldValue) {}
	int32 HP;
	virtual void onHPChanged(int32 oldValue) {}
	FString Name;
	virtual void onNameChanged(const FString& oldValue) {}
	float PowerRatio;
	virtual void onPowerRatioChanged(float oldValue) {}
	uint8 RoleType;
	virtual void onRoleTypeChanged(uint8 oldValue) {}
	FVector SpawnPoint;
	virtual void onSpawnPointChanged(const FVector& oldValue) {}
	float SpeedRatio;
	virtual void onSpeedRatioChanged(float oldValue) {}

	virtual void AcceptChatList(const CHAT_LIST& arg1) = 0; 
	virtual void OnAnimUpdate(const ANIM_INFO& arg1) = 0; 
	virtual void OnAttack() = 0; 
	virtual void OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2) = 0; 
	virtual void OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4) = 0; 
	virtual void OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3) = 0; 
	virtual void OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4) = 0; 

	void onComponentsEnterworld() override;
	void onComponentsLeaveworld() override;

	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;


	void onRemoteMethodCall(MemoryStream& stream) override;
	void onUpdatePropertys(MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	ExRoleBase();
	virtual ~ExRoleBase();

	void attachComponents() override;
	void detachComponents() override;

};

}