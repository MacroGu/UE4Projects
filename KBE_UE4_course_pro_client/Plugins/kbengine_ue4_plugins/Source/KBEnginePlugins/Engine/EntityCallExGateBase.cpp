#include "EntityCallExGateBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExGateBase::EntityBaseEntityCall_ExGateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExGateBase::~EntityBaseEntityCall_ExGateBase()
{
}



EntityCellEntityCall_ExGateBase::EntityCellEntityCall_ExGateBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExGateBase::~EntityCellEntityCall_ExGateBase()
{
}


}