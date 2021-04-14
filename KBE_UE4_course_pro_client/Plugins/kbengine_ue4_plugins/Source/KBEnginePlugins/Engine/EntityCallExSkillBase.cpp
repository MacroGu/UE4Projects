#include "EntityCallExSkillBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExSkillBase::EntityBaseEntityCall_ExSkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExSkillBase::~EntityBaseEntityCall_ExSkillBase()
{
}



EntityCellEntityCall_ExSkillBase::EntityCellEntityCall_ExSkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExSkillBase::~EntityCellEntityCall_ExSkillBase()
{
}


}