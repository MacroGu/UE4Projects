#include "EntityCallExRoomBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExRoomBase::EntityBaseEntityCall_ExRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExRoomBase::~EntityBaseEntityCall_ExRoomBase()
{
}



EntityCellEntityCall_ExRoomBase::EntityCellEntityCall_ExRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExRoomBase::~EntityCellEntityCall_ExRoomBase()
{
}


}