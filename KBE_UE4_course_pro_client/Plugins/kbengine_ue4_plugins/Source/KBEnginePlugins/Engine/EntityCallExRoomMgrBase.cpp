#include "EntityCallExRoomMgrBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExRoomMgrBase::EntityBaseEntityCall_ExRoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExRoomMgrBase::~EntityBaseEntityCall_ExRoomMgrBase()
{
}



EntityCellEntityCall_ExRoomMgrBase::EntityCellEntityCall_ExRoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExRoomMgrBase::~EntityCellEntityCall_ExRoomMgrBase()
{
}


}