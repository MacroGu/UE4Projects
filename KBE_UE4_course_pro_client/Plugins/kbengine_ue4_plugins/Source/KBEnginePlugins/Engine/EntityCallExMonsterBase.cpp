#include "EntityCallExMonsterBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExMonsterBase::EntityBaseEntityCall_ExMonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExMonsterBase::~EntityBaseEntityCall_ExMonsterBase()
{
}



EntityCellEntityCall_ExMonsterBase::EntityCellEntityCall_ExMonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExMonsterBase::~EntityCellEntityCall_ExMonsterBase()
{
}

void EntityCellEntityCall_ExMonsterBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[30])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_ExMonsterBase::Attack(const SKILL_INFO& arg1)
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[34])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_ExMonsterBase::Relive()
{
	Bundle* pBundleRet = newCall("Relive", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}


}