#include "EntityCallExFlobBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExFlobBase::EntityBaseEntityCall_ExFlobBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExFlobBase::~EntityBaseEntityCall_ExFlobBase()
{
}



EntityCellEntityCall_ExFlobBase::EntityCellEntityCall_ExFlobBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExFlobBase::~EntityCellEntityCall_ExFlobBase()
{
}


}