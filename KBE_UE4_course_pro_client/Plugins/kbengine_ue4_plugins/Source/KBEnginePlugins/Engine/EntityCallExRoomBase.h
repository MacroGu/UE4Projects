/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"


// defined in */scripts/entity_defs/ExRoom.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_ExRoomBase : public EntityCall
{
public:

	EntityBaseEntityCall_ExRoomBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_ExRoomBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_ExRoomBase : public EntityCall
{
public:

	EntityCellEntityCall_ExRoomBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_ExRoomBase();
};

}