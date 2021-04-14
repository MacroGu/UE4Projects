#include "EntityCallExAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExAccountBase::EntityBaseEntityCall_ExAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExAccountBase::~EntityBaseEntityCall_ExAccountBase()
{
}

void EntityBaseEntityCall_ExAccountBase::ReqCreateRole(uint8 arg1, const FString& arg2)
{
	Bundle* pBundleRet = newCall("ReqCreateRole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUnicode(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::ReqCreateRoom(const FString& arg1)
{
	Bundle* pBundleRet = newCall("ReqCreateRoom", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::ReqRemoveRole(const FString& arg1)
{
	Bundle* pBundleRet = newCall("ReqRemoveRole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::ReqRoleList()
{
	Bundle* pBundleRet = newCall("ReqRoleList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::ReqRoomList()
{
	Bundle* pBundleRet = newCall("ReqRoomList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::ReqSelectRoleGame(uint64 arg1)
{
	Bundle* pBundleRet = newCall("ReqSelectRoleGame", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_ExAccountBase::SelectRoomGame(uint64 arg1)
{
	Bundle* pBundleRet = newCall("SelectRoomGame", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_ExAccountBase::EntityCellEntityCall_ExAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExAccountBase::~EntityCellEntityCall_ExAccountBase()
{
}


}