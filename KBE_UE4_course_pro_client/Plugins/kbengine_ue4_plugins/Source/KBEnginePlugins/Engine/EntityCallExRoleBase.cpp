#include "EntityCallExRoleBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExRoleBase::EntityBaseEntityCall_ExRoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExRoleBase::~EntityBaseEntityCall_ExRoleBase()
{
}

void EntityBaseEntityCall_ExRoleBase::LeaveRoom()
{
	Bundle* pBundleRet = newCall("LeaveRoom", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_ExRoleBase::PassGood(uint8 arg1, uint8 arg2, uint8 arg3, uint8 arg4)
{
	Bundle* pBundleRet = newCall("PassGood", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUint8(arg2);
	pBundleRet->writeUint8(arg3);
	pBundleRet->writeUint8(arg4);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExRoleBase::ReduceGood(uint8 arg1, uint8 arg2)
{
	Bundle* pBundleRet = newCall("ReduceGood", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUint8(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExRoleBase::ReqBagList()
{
	Bundle* pBundleRet = newCall("ReqBagList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_ExRoleBase::ReqTeleportRoom(uint64 arg1)
{
	Bundle* pBundleRet = newCall("ReqTeleportRoom", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExRoleBase::SendChatInfo(const FString& arg1)
{
	Bundle* pBundleRet = newCall("SendChatInfo", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_ExRoleBase::EntityCellEntityCall_ExRoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExRoleBase::~EntityCellEntityCall_ExRoleBase()
{
}

void EntityCellEntityCall_ExRoleBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[30])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_ExRoleBase::Attack(const SKILL_INFO& arg1)
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[34])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_ExRoleBase::Relive()
{
	Bundle* pBundleRet = newCall("Relive", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}


}