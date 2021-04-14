#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/ExAccount.h"
#include "Scripts/ExRole.h"
#include "Scripts/ExMonster.h"
#include "Scripts/ExSkill.h"
#include "Scripts/ExFlob.h"
#include "Scripts/ExGate.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new ExAccount();
			break;
		case 2:
			pEntity = new ExRole();
			break;
		case 5:
			pEntity = new ExMonster();
			break;
		case 6:
			pEntity = new ExSkill();
			break;
		case 7:
			pEntity = new ExFlob();
			break;
		case 8:
			pEntity = new ExGate();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pExAccountModule = new ScriptModule("ExAccount", 1);
	EntityDef::moduledefs.Add(TEXT("ExAccount"), pExAccountModule);
	EntityDef::idmoduledefs.Add(1, pExAccountModule);

	Property* pExAccount_position = new Property();
	pExAccount_position->name = TEXT("position");
	pExAccount_position->properUtype = 40000;
	pExAccount_position->properFlags = 4;
	pExAccount_position->aliasID = 1;
	KBVar* pExAccount_position_defval = new KBVar(FVector());
	pExAccount_position->pDefaultVal = pExAccount_position_defval;
	pExAccountModule->propertys.Add(TEXT("position"), pExAccount_position); 

	pExAccountModule->usePropertyDescrAlias = true;
	pExAccountModule->idpropertys.Add((uint16)pExAccount_position->aliasID, pExAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), property(position / 40000).");

	Property* pExAccount_direction = new Property();
	pExAccount_direction->name = TEXT("direction");
	pExAccount_direction->properUtype = 40001;
	pExAccount_direction->properFlags = 4;
	pExAccount_direction->aliasID = 2;
	KBVar* pExAccount_direction_defval = new KBVar(FVector());
	pExAccount_direction->pDefaultVal = pExAccount_direction_defval;
	pExAccountModule->propertys.Add(TEXT("direction"), pExAccount_direction); 

	pExAccountModule->usePropertyDescrAlias = true;
	pExAccountModule->idpropertys.Add((uint16)pExAccount_direction->aliasID, pExAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), property(direction / 40001).");

	Property* pExAccount_spaceID = new Property();
	pExAccount_spaceID->name = TEXT("spaceID");
	pExAccount_spaceID->properUtype = 40002;
	pExAccount_spaceID->properFlags = 16;
	pExAccount_spaceID->aliasID = 3;
	KBVar* pExAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExAccount_spaceID->pDefaultVal = pExAccount_spaceID_defval;
	pExAccountModule->propertys.Add(TEXT("spaceID"), pExAccount_spaceID); 

	pExAccountModule->usePropertyDescrAlias = true;
	pExAccountModule->idpropertys.Add((uint16)pExAccount_spaceID->aliasID, pExAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), property(spaceID / 40002).");

	Property* pExAccount_LastSelRole = new Property();
	pExAccount_LastSelRole->name = TEXT("LastSelRole");
	pExAccount_LastSelRole->properUtype = 2;
	pExAccount_LastSelRole->properFlags = 32;
	pExAccount_LastSelRole->aliasID = 4;
	KBVar* pExAccount_LastSelRole_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pExAccount_LastSelRole->pDefaultVal = pExAccount_LastSelRole_defval;
	pExAccountModule->propertys.Add(TEXT("LastSelRole"), pExAccount_LastSelRole); 

	pExAccountModule->usePropertyDescrAlias = true;
	pExAccountModule->idpropertys.Add((uint16)pExAccount_LastSelRole->aliasID, pExAccount_LastSelRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), property(LastSelRole / 2).");

	TArray<DATATYPE_BASE*> ExAccount_OnCreateRole_args;
	ExAccount_OnCreateRole_args.Add(EntityDef::id2datatypes[2]);
	ExAccount_OnCreateRole_args.Add(EntityDef::id2datatypes[24]);

	Method* pExAccount_OnCreateRole = new Method();
	pExAccount_OnCreateRole->name = TEXT("OnCreateRole");
	pExAccount_OnCreateRole->methodUtype = 9;
	pExAccount_OnCreateRole->aliasID = 1;
	pExAccount_OnCreateRole->args = ExAccount_OnCreateRole_args;

	pExAccountModule->methods.Add(TEXT("OnCreateRole"), pExAccount_OnCreateRole); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnCreateRole->aliasID, pExAccount_OnCreateRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnCreateRole / 9).");

	TArray<DATATYPE_BASE*> ExAccount_OnCreateRoom_args;
	ExAccount_OnCreateRoom_args.Add(EntityDef::id2datatypes[2]);
	ExAccount_OnCreateRoom_args.Add(EntityDef::id2datatypes[27]);

	Method* pExAccount_OnCreateRoom = new Method();
	pExAccount_OnCreateRoom->name = TEXT("OnCreateRoom");
	pExAccount_OnCreateRoom->methodUtype = 13;
	pExAccount_OnCreateRoom->aliasID = 2;
	pExAccount_OnCreateRoom->args = ExAccount_OnCreateRoom_args;

	pExAccountModule->methods.Add(TEXT("OnCreateRoom"), pExAccount_OnCreateRoom); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnCreateRoom->aliasID, pExAccount_OnCreateRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnCreateRoom / 13).");

	TArray<DATATYPE_BASE*> ExAccount_OnRemoveRole_args;
	ExAccount_OnRemoveRole_args.Add(EntityDef::id2datatypes[5]);

	Method* pExAccount_OnRemoveRole = new Method();
	pExAccount_OnRemoveRole->name = TEXT("OnRemoveRole");
	pExAccount_OnRemoveRole->methodUtype = 10;
	pExAccount_OnRemoveRole->aliasID = 3;
	pExAccount_OnRemoveRole->args = ExAccount_OnRemoveRole_args;

	pExAccountModule->methods.Add(TEXT("OnRemoveRole"), pExAccount_OnRemoveRole); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnRemoveRole->aliasID, pExAccount_OnRemoveRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnRemoveRole / 10).");

	TArray<DATATYPE_BASE*> ExAccount_OnReqRoleList_args;
	ExAccount_OnReqRoleList_args.Add(EntityDef::id2datatypes[25]);

	Method* pExAccount_OnReqRoleList = new Method();
	pExAccount_OnReqRoleList->name = TEXT("OnReqRoleList");
	pExAccount_OnReqRoleList->methodUtype = 8;
	pExAccount_OnReqRoleList->aliasID = 4;
	pExAccount_OnReqRoleList->args = ExAccount_OnReqRoleList_args;

	pExAccountModule->methods.Add(TEXT("OnReqRoleList"), pExAccount_OnReqRoleList); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnReqRoleList->aliasID, pExAccount_OnReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnReqRoleList / 8).");

	TArray<DATATYPE_BASE*> ExAccount_OnReqRoomList_args;
	ExAccount_OnReqRoomList_args.Add(EntityDef::id2datatypes[28]);

	Method* pExAccount_OnReqRoomList = new Method();
	pExAccount_OnReqRoomList->name = TEXT("OnReqRoomList");
	pExAccount_OnReqRoomList->methodUtype = 12;
	pExAccount_OnReqRoomList->aliasID = 5;
	pExAccount_OnReqRoomList->args = ExAccount_OnReqRoomList_args;

	pExAccountModule->methods.Add(TEXT("OnReqRoomList"), pExAccount_OnReqRoomList); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnReqRoomList->aliasID, pExAccount_OnReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnReqRoomList / 12).");

	TArray<DATATYPE_BASE*> ExAccount_OnSelectRoleGame_args;
	ExAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[2]);
	ExAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pExAccount_OnSelectRoleGame = new Method();
	pExAccount_OnSelectRoleGame->name = TEXT("OnSelectRoleGame");
	pExAccount_OnSelectRoleGame->methodUtype = 11;
	pExAccount_OnSelectRoleGame->aliasID = 6;
	pExAccount_OnSelectRoleGame->args = ExAccount_OnSelectRoleGame_args;

	pExAccountModule->methods.Add(TEXT("OnSelectRoleGame"), pExAccount_OnSelectRoleGame); 
	pExAccountModule->useMethodDescrAlias = true;
	pExAccountModule->idmethods.Add((uint16)pExAccount_OnSelectRoleGame->aliasID, pExAccount_OnSelectRoleGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(OnSelectRoleGame / 11).");

	TArray<DATATYPE_BASE*> ExAccount_ReqCreateRole_args;
	ExAccount_ReqCreateRole_args.Add(EntityDef::id2datatypes[2]);
	ExAccount_ReqCreateRole_args.Add(EntityDef::id2datatypes[12]);

	Method* pExAccount_ReqCreateRole = new Method();
	pExAccount_ReqCreateRole->name = TEXT("ReqCreateRole");
	pExAccount_ReqCreateRole->methodUtype = 2;
	pExAccount_ReqCreateRole->aliasID = -1;
	pExAccount_ReqCreateRole->args = ExAccount_ReqCreateRole_args;

	pExAccountModule->methods.Add(TEXT("ReqCreateRole"), pExAccount_ReqCreateRole); 
	pExAccountModule->base_methods.Add(TEXT("ReqCreateRole"), pExAccount_ReqCreateRole);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqCreateRole->methodUtype, pExAccount_ReqCreateRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqCreateRole / 2).");

	TArray<DATATYPE_BASE*> ExAccount_ReqCreateRoom_args;
	ExAccount_ReqCreateRoom_args.Add(EntityDef::id2datatypes[12]);

	Method* pExAccount_ReqCreateRoom = new Method();
	pExAccount_ReqCreateRoom->name = TEXT("ReqCreateRoom");
	pExAccount_ReqCreateRoom->methodUtype = 6;
	pExAccount_ReqCreateRoom->aliasID = -1;
	pExAccount_ReqCreateRoom->args = ExAccount_ReqCreateRoom_args;

	pExAccountModule->methods.Add(TEXT("ReqCreateRoom"), pExAccount_ReqCreateRoom); 
	pExAccountModule->base_methods.Add(TEXT("ReqCreateRoom"), pExAccount_ReqCreateRoom);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqCreateRoom->methodUtype, pExAccount_ReqCreateRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqCreateRoom / 6).");

	TArray<DATATYPE_BASE*> ExAccount_ReqRemoveRole_args;
	ExAccount_ReqRemoveRole_args.Add(EntityDef::id2datatypes[12]);

	Method* pExAccount_ReqRemoveRole = new Method();
	pExAccount_ReqRemoveRole->name = TEXT("ReqRemoveRole");
	pExAccount_ReqRemoveRole->methodUtype = 3;
	pExAccount_ReqRemoveRole->aliasID = -1;
	pExAccount_ReqRemoveRole->args = ExAccount_ReqRemoveRole_args;

	pExAccountModule->methods.Add(TEXT("ReqRemoveRole"), pExAccount_ReqRemoveRole); 
	pExAccountModule->base_methods.Add(TEXT("ReqRemoveRole"), pExAccount_ReqRemoveRole);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqRemoveRole->methodUtype, pExAccount_ReqRemoveRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqRemoveRole / 3).");

	TArray<DATATYPE_BASE*> ExAccount_ReqRoleList_args;

	Method* pExAccount_ReqRoleList = new Method();
	pExAccount_ReqRoleList->name = TEXT("ReqRoleList");
	pExAccount_ReqRoleList->methodUtype = 1;
	pExAccount_ReqRoleList->aliasID = -1;
	pExAccount_ReqRoleList->args = ExAccount_ReqRoleList_args;

	pExAccountModule->methods.Add(TEXT("ReqRoleList"), pExAccount_ReqRoleList); 
	pExAccountModule->base_methods.Add(TEXT("ReqRoleList"), pExAccount_ReqRoleList);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqRoleList->methodUtype, pExAccount_ReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqRoleList / 1).");

	TArray<DATATYPE_BASE*> ExAccount_ReqRoomList_args;

	Method* pExAccount_ReqRoomList = new Method();
	pExAccount_ReqRoomList->name = TEXT("ReqRoomList");
	pExAccount_ReqRoomList->methodUtype = 5;
	pExAccount_ReqRoomList->aliasID = -1;
	pExAccount_ReqRoomList->args = ExAccount_ReqRoomList_args;

	pExAccountModule->methods.Add(TEXT("ReqRoomList"), pExAccount_ReqRoomList); 
	pExAccountModule->base_methods.Add(TEXT("ReqRoomList"), pExAccount_ReqRoomList);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqRoomList->methodUtype, pExAccount_ReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqRoomList / 5).");

	TArray<DATATYPE_BASE*> ExAccount_ReqSelectRoleGame_args;
	ExAccount_ReqSelectRoleGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pExAccount_ReqSelectRoleGame = new Method();
	pExAccount_ReqSelectRoleGame->name = TEXT("ReqSelectRoleGame");
	pExAccount_ReqSelectRoleGame->methodUtype = 4;
	pExAccount_ReqSelectRoleGame->aliasID = -1;
	pExAccount_ReqSelectRoleGame->args = ExAccount_ReqSelectRoleGame_args;

	pExAccountModule->methods.Add(TEXT("ReqSelectRoleGame"), pExAccount_ReqSelectRoleGame); 
	pExAccountModule->base_methods.Add(TEXT("ReqSelectRoleGame"), pExAccount_ReqSelectRoleGame);

	pExAccountModule->idbase_methods.Add(pExAccount_ReqSelectRoleGame->methodUtype, pExAccount_ReqSelectRoleGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(ReqSelectRoleGame / 4).");

	TArray<DATATYPE_BASE*> ExAccount_SelectRoomGame_args;
	ExAccount_SelectRoomGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pExAccount_SelectRoomGame = new Method();
	pExAccount_SelectRoomGame->name = TEXT("SelectRoomGame");
	pExAccount_SelectRoomGame->methodUtype = 7;
	pExAccount_SelectRoomGame->aliasID = -1;
	pExAccount_SelectRoomGame->args = ExAccount_SelectRoomGame_args;

	pExAccountModule->methods.Add(TEXT("SelectRoomGame"), pExAccount_SelectRoomGame); 
	pExAccountModule->base_methods.Add(TEXT("SelectRoomGame"), pExAccount_SelectRoomGame);

	pExAccountModule->idbase_methods.Add(pExAccount_SelectRoomGame->methodUtype, pExAccount_SelectRoomGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExAccount), method(SelectRoomGame / 7).");

	ScriptModule* pExRoleModule = new ScriptModule("ExRole", 2);
	EntityDef::moduledefs.Add(TEXT("ExRole"), pExRoleModule);
	EntityDef::idmoduledefs.Add(2, pExRoleModule);

	Property* pExRole_position = new Property();
	pExRole_position->name = TEXT("position");
	pExRole_position->properUtype = 40000;
	pExRole_position->properFlags = 4;
	pExRole_position->aliasID = 1;
	KBVar* pExRole_position_defval = new KBVar(FVector());
	pExRole_position->pDefaultVal = pExRole_position_defval;
	pExRoleModule->propertys.Add(TEXT("position"), pExRole_position); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_position->aliasID, pExRole_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(position / 40000).");

	Property* pExRole_direction = new Property();
	pExRole_direction->name = TEXT("direction");
	pExRole_direction->properUtype = 40001;
	pExRole_direction->properFlags = 4;
	pExRole_direction->aliasID = 2;
	KBVar* pExRole_direction_defval = new KBVar(FVector());
	pExRole_direction->pDefaultVal = pExRole_direction_defval;
	pExRoleModule->propertys.Add(TEXT("direction"), pExRole_direction); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_direction->aliasID, pExRole_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(direction / 40001).");

	Property* pExRole_spaceID = new Property();
	pExRole_spaceID->name = TEXT("spaceID");
	pExRole_spaceID->properUtype = 40002;
	pExRole_spaceID->properFlags = 16;
	pExRole_spaceID->aliasID = 3;
	KBVar* pExRole_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExRole_spaceID->pDefaultVal = pExRole_spaceID_defval;
	pExRoleModule->propertys.Add(TEXT("spaceID"), pExRole_spaceID); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_spaceID->aliasID, pExRole_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(spaceID / 40002).");

	Property* pExRole_BaseHP = new Property();
	pExRole_BaseHP->name = TEXT("BaseHP");
	pExRole_BaseHP->properUtype = 12;
	pExRole_BaseHP->properFlags = 4;
	pExRole_BaseHP->aliasID = 4;
	KBVar* pExRole_BaseHP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pExRole_BaseHP->pDefaultVal = pExRole_BaseHP_defval;
	pExRoleModule->propertys.Add(TEXT("BaseHP"), pExRole_BaseHP); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_BaseHP->aliasID, pExRole_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(BaseHP / 12).");

	Property* pExRole_Defense = new Property();
	pExRole_Defense->name = TEXT("Defense");
	pExRole_Defense->properUtype = 14;
	pExRole_Defense->properFlags = 16;
	pExRole_Defense->aliasID = 5;
	KBVar* pExRole_Defense_defval = new KBVar((int32)FCString::Atoi64(TEXT("10")));
	pExRole_Defense->pDefaultVal = pExRole_Defense_defval;
	pExRoleModule->propertys.Add(TEXT("Defense"), pExRole_Defense); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_Defense->aliasID, pExRole_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(Defense / 14).");

	Property* pExRole_HP = new Property();
	pExRole_HP->name = TEXT("HP");
	pExRole_HP->properUtype = 13;
	pExRole_HP->properFlags = 4;
	pExRole_HP->aliasID = 6;
	KBVar* pExRole_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pExRole_HP->pDefaultVal = pExRole_HP_defval;
	pExRoleModule->propertys.Add(TEXT("HP"), pExRole_HP); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_HP->aliasID, pExRole_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(HP / 13).");

	Property* pExRole_Name = new Property();
	pExRole_Name->name = TEXT("Name");
	pExRole_Name->properUtype = 10;
	pExRole_Name->properFlags = 4;
	pExRole_Name->aliasID = 7;
	KBVar* pExRole_Name_defval = new KBVar(FString());
	pExRole_Name->pDefaultVal = pExRole_Name_defval;
	pExRoleModule->propertys.Add(TEXT("Name"), pExRole_Name); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_Name->aliasID, pExRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(Name / 10).");

	Property* pExRole_PowerRatio = new Property();
	pExRole_PowerRatio->name = TEXT("PowerRatio");
	pExRole_PowerRatio->properUtype = 15;
	pExRole_PowerRatio->properFlags = 16;
	pExRole_PowerRatio->aliasID = 8;
	KBVar* pExRole_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pExRole_PowerRatio->pDefaultVal = pExRole_PowerRatio_defval;
	pExRoleModule->propertys.Add(TEXT("PowerRatio"), pExRole_PowerRatio); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_PowerRatio->aliasID, pExRole_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(PowerRatio / 15).");

	Property* pExRole_RoleType = new Property();
	pExRole_RoleType->name = TEXT("RoleType");
	pExRole_RoleType->properUtype = 11;
	pExRole_RoleType->properFlags = 4;
	pExRole_RoleType->aliasID = 9;
	KBVar* pExRole_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pExRole_RoleType->pDefaultVal = pExRole_RoleType_defval;
	pExRoleModule->propertys.Add(TEXT("RoleType"), pExRole_RoleType); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_RoleType->aliasID, pExRole_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(RoleType / 11).");

	Property* pExRole_SpawnPoint = new Property();
	pExRole_SpawnPoint->name = TEXT("SpawnPoint");
	pExRole_SpawnPoint->properUtype = 4;
	pExRole_SpawnPoint->properFlags = 16;
	pExRole_SpawnPoint->aliasID = 10;
	KBVar* pExRole_SpawnPoint_defval = new KBVar(FVector());
	pExRole_SpawnPoint->pDefaultVal = pExRole_SpawnPoint_defval;
	pExRoleModule->propertys.Add(TEXT("SpawnPoint"), pExRole_SpawnPoint); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_SpawnPoint->aliasID, pExRole_SpawnPoint);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(SpawnPoint / 4).");

	Property* pExRole_SpeedRatio = new Property();
	pExRole_SpeedRatio->name = TEXT("SpeedRatio");
	pExRole_SpeedRatio->properUtype = 16;
	pExRole_SpeedRatio->properFlags = 16;
	pExRole_SpeedRatio->aliasID = 11;
	KBVar* pExRole_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pExRole_SpeedRatio->pDefaultVal = pExRole_SpeedRatio_defval;
	pExRoleModule->propertys.Add(TEXT("SpeedRatio"), pExRole_SpeedRatio); 

	pExRoleModule->usePropertyDescrAlias = true;
	pExRoleModule->idpropertys.Add((uint16)pExRole_SpeedRatio->aliasID, pExRole_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), property(SpeedRatio / 16).");

	TArray<DATATYPE_BASE*> ExRole_AcceptChatList_args;
	ExRole_AcceptChatList_args.Add(EntityDef::id2datatypes[36]);

	Method* pExRole_AcceptChatList = new Method();
	pExRole_AcceptChatList->name = TEXT("AcceptChatList");
	pExRole_AcceptChatList->methodUtype = 27;
	pExRole_AcceptChatList->aliasID = 1;
	pExRole_AcceptChatList->args = ExRole_AcceptChatList_args;

	pExRoleModule->methods.Add(TEXT("AcceptChatList"), pExRole_AcceptChatList); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_AcceptChatList->aliasID, pExRole_AcceptChatList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(AcceptChatList / 27).");

	TArray<DATATYPE_BASE*> ExRole_OnAnimUpdate_args;
	ExRole_OnAnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pExRole_OnAnimUpdate = new Method();
	pExRole_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pExRole_OnAnimUpdate->methodUtype = 36;
	pExRole_OnAnimUpdate->aliasID = 2;
	pExRole_OnAnimUpdate->args = ExRole_OnAnimUpdate_args;

	pExRoleModule->methods.Add(TEXT("OnAnimUpdate"), pExRole_OnAnimUpdate); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnAnimUpdate->aliasID, pExRole_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnAnimUpdate / 36).");

	TArray<DATATYPE_BASE*> ExRole_OnAttack_args;

	Method* pExRole_OnAttack = new Method();
	pExRole_OnAttack->name = TEXT("OnAttack");
	pExRole_OnAttack->methodUtype = 34;
	pExRole_OnAttack->aliasID = 3;
	pExRole_OnAttack->args = ExRole_OnAttack_args;

	pExRoleModule->methods.Add(TEXT("OnAttack"), pExRole_OnAttack); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnAttack->aliasID, pExRole_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnAttack / 34).");

	TArray<DATATYPE_BASE*> ExRole_OnIncreaseGood_args;
	ExRole_OnIncreaseGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_OnIncreaseGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pExRole_OnIncreaseGood = new Method();
	pExRole_OnIncreaseGood->name = TEXT("OnIncreaseGood");
	pExRole_OnIncreaseGood->methodUtype = 24;
	pExRole_OnIncreaseGood->aliasID = 4;
	pExRole_OnIncreaseGood->args = ExRole_OnIncreaseGood_args;

	pExRoleModule->methods.Add(TEXT("OnIncreaseGood"), pExRole_OnIncreaseGood); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnIncreaseGood->aliasID, pExRole_OnIncreaseGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnIncreaseGood / 24).");

	TArray<DATATYPE_BASE*> ExRole_OnPassGood_args;
	ExRole_OnPassGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_OnPassGood_args.Add(EntityDef::id2datatypes[31]);
	ExRole_OnPassGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_OnPassGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pExRole_OnPassGood = new Method();
	pExRole_OnPassGood->name = TEXT("OnPassGood");
	pExRole_OnPassGood->methodUtype = 26;
	pExRole_OnPassGood->aliasID = 5;
	pExRole_OnPassGood->args = ExRole_OnPassGood_args;

	pExRoleModule->methods.Add(TEXT("OnPassGood"), pExRole_OnPassGood); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnPassGood->aliasID, pExRole_OnPassGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnPassGood / 26).");

	TArray<DATATYPE_BASE*> ExRole_OnReduceGood_args;
	ExRole_OnReduceGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_OnReduceGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_OnReduceGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pExRole_OnReduceGood = new Method();
	pExRole_OnReduceGood->name = TEXT("OnReduceGood");
	pExRole_OnReduceGood->methodUtype = 25;
	pExRole_OnReduceGood->aliasID = 6;
	pExRole_OnReduceGood->args = ExRole_OnReduceGood_args;

	pExRoleModule->methods.Add(TEXT("OnReduceGood"), pExRole_OnReduceGood); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnReduceGood->aliasID, pExRole_OnReduceGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnReduceGood / 25).");

	TArray<DATATYPE_BASE*> ExRole_OnReqBagList_args;
	ExRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	ExRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	ExRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	ExRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);

	Method* pExRole_OnReqBagList = new Method();
	pExRole_OnReqBagList->name = TEXT("OnReqBagList");
	pExRole_OnReqBagList->methodUtype = 23;
	pExRole_OnReqBagList->aliasID = 7;
	pExRole_OnReqBagList->args = ExRole_OnReqBagList_args;

	pExRoleModule->methods.Add(TEXT("OnReqBagList"), pExRole_OnReqBagList); 
	pExRoleModule->useMethodDescrAlias = true;
	pExRoleModule->idmethods.Add((uint16)pExRole_OnReqBagList->aliasID, pExRole_OnReqBagList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(OnReqBagList / 23).");

	TArray<DATATYPE_BASE*> ExRole_LeaveRoom_args;

	Method* pExRole_LeaveRoom = new Method();
	pExRole_LeaveRoom->name = TEXT("LeaveRoom");
	pExRole_LeaveRoom->methodUtype = 20;
	pExRole_LeaveRoom->aliasID = -1;
	pExRole_LeaveRoom->args = ExRole_LeaveRoom_args;

	pExRoleModule->methods.Add(TEXT("LeaveRoom"), pExRole_LeaveRoom); 
	pExRoleModule->base_methods.Add(TEXT("LeaveRoom"), pExRole_LeaveRoom);

	pExRoleModule->idbase_methods.Add(pExRole_LeaveRoom->methodUtype, pExRole_LeaveRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(LeaveRoom / 20).");

	TArray<DATATYPE_BASE*> ExRole_PassGood_args;
	ExRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_PassGood_args.Add(EntityDef::id2datatypes[2]);

	Method* pExRole_PassGood = new Method();
	pExRole_PassGood->name = TEXT("PassGood");
	pExRole_PassGood->methodUtype = 18;
	pExRole_PassGood->aliasID = -1;
	pExRole_PassGood->args = ExRole_PassGood_args;

	pExRoleModule->methods.Add(TEXT("PassGood"), pExRole_PassGood); 
	pExRoleModule->base_methods.Add(TEXT("PassGood"), pExRole_PassGood);

	pExRoleModule->idbase_methods.Add(pExRole_PassGood->methodUtype, pExRole_PassGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(PassGood / 18).");

	TArray<DATATYPE_BASE*> ExRole_ReduceGood_args;
	ExRole_ReduceGood_args.Add(EntityDef::id2datatypes[2]);
	ExRole_ReduceGood_args.Add(EntityDef::id2datatypes[2]);

	Method* pExRole_ReduceGood = new Method();
	pExRole_ReduceGood->name = TEXT("ReduceGood");
	pExRole_ReduceGood->methodUtype = 17;
	pExRole_ReduceGood->aliasID = -1;
	pExRole_ReduceGood->args = ExRole_ReduceGood_args;

	pExRoleModule->methods.Add(TEXT("ReduceGood"), pExRole_ReduceGood); 
	pExRoleModule->base_methods.Add(TEXT("ReduceGood"), pExRole_ReduceGood);

	pExRoleModule->idbase_methods.Add(pExRole_ReduceGood->methodUtype, pExRole_ReduceGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(ReduceGood / 17).");

	TArray<DATATYPE_BASE*> ExRole_ReqBagList_args;

	Method* pExRole_ReqBagList = new Method();
	pExRole_ReqBagList->name = TEXT("ReqBagList");
	pExRole_ReqBagList->methodUtype = 15;
	pExRole_ReqBagList->aliasID = -1;
	pExRole_ReqBagList->args = ExRole_ReqBagList_args;

	pExRoleModule->methods.Add(TEXT("ReqBagList"), pExRole_ReqBagList); 
	pExRoleModule->base_methods.Add(TEXT("ReqBagList"), pExRole_ReqBagList);

	pExRoleModule->idbase_methods.Add(pExRole_ReqBagList->methodUtype, pExRole_ReqBagList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(ReqBagList / 15).");

	TArray<DATATYPE_BASE*> ExRole_ReqTeleportRoom_args;
	ExRole_ReqTeleportRoom_args.Add(EntityDef::id2datatypes[5]);

	Method* pExRole_ReqTeleportRoom = new Method();
	pExRole_ReqTeleportRoom->name = TEXT("ReqTeleportRoom");
	pExRole_ReqTeleportRoom->methodUtype = 21;
	pExRole_ReqTeleportRoom->aliasID = -1;
	pExRole_ReqTeleportRoom->args = ExRole_ReqTeleportRoom_args;

	pExRoleModule->methods.Add(TEXT("ReqTeleportRoom"), pExRole_ReqTeleportRoom); 
	pExRoleModule->base_methods.Add(TEXT("ReqTeleportRoom"), pExRole_ReqTeleportRoom);

	pExRoleModule->idbase_methods.Add(pExRole_ReqTeleportRoom->methodUtype, pExRole_ReqTeleportRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(ReqTeleportRoom / 21).");

	TArray<DATATYPE_BASE*> ExRole_SendChatInfo_args;
	ExRole_SendChatInfo_args.Add(EntityDef::id2datatypes[12]);

	Method* pExRole_SendChatInfo = new Method();
	pExRole_SendChatInfo->name = TEXT("SendChatInfo");
	pExRole_SendChatInfo->methodUtype = 19;
	pExRole_SendChatInfo->aliasID = -1;
	pExRole_SendChatInfo->args = ExRole_SendChatInfo_args;

	pExRoleModule->methods.Add(TEXT("SendChatInfo"), pExRole_SendChatInfo); 
	pExRoleModule->base_methods.Add(TEXT("SendChatInfo"), pExRole_SendChatInfo);

	pExRoleModule->idbase_methods.Add(pExRole_SendChatInfo->methodUtype, pExRole_SendChatInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(SendChatInfo / 19).");

	TArray<DATATYPE_BASE*> ExRole_AnimUpdate_args;
	ExRole_AnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pExRole_AnimUpdate = new Method();
	pExRole_AnimUpdate->name = TEXT("AnimUpdate");
	pExRole_AnimUpdate->methodUtype = 35;
	pExRole_AnimUpdate->aliasID = -1;
	pExRole_AnimUpdate->args = ExRole_AnimUpdate_args;

	pExRoleModule->methods.Add(TEXT("AnimUpdate"), pExRole_AnimUpdate); 
	pExRoleModule->cell_methods.Add(TEXT("AnimUpdate"), pExRole_AnimUpdate);

	pExRoleModule->idcell_methods.Add(pExRole_AnimUpdate->methodUtype, pExRole_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(AnimUpdate / 35).");

	TArray<DATATYPE_BASE*> ExRole_Attack_args;
	ExRole_Attack_args.Add(EntityDef::id2datatypes[34]);

	Method* pExRole_Attack = new Method();
	pExRole_Attack->name = TEXT("Attack");
	pExRole_Attack->methodUtype = 28;
	pExRole_Attack->aliasID = -1;
	pExRole_Attack->args = ExRole_Attack_args;

	pExRoleModule->methods.Add(TEXT("Attack"), pExRole_Attack); 
	pExRoleModule->cell_methods.Add(TEXT("Attack"), pExRole_Attack);

	pExRoleModule->idcell_methods.Add(pExRole_Attack->methodUtype, pExRole_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(Attack / 28).");

	TArray<DATATYPE_BASE*> ExRole_Relive_args;

	Method* pExRole_Relive = new Method();
	pExRole_Relive->name = TEXT("Relive");
	pExRole_Relive->methodUtype = 29;
	pExRole_Relive->aliasID = -1;
	pExRole_Relive->args = ExRole_Relive_args;

	pExRoleModule->methods.Add(TEXT("Relive"), pExRole_Relive); 
	pExRoleModule->cell_methods.Add(TEXT("Relive"), pExRole_Relive);

	pExRoleModule->idcell_methods.Add(pExRole_Relive->methodUtype, pExRole_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExRole), method(Relive / 29).");

	ScriptModule* pExMonsterModule = new ScriptModule("ExMonster", 5);
	EntityDef::moduledefs.Add(TEXT("ExMonster"), pExMonsterModule);
	EntityDef::idmoduledefs.Add(5, pExMonsterModule);

	Property* pExMonster_position = new Property();
	pExMonster_position->name = TEXT("position");
	pExMonster_position->properUtype = 40000;
	pExMonster_position->properFlags = 4;
	pExMonster_position->aliasID = 1;
	KBVar* pExMonster_position_defval = new KBVar(FVector());
	pExMonster_position->pDefaultVal = pExMonster_position_defval;
	pExMonsterModule->propertys.Add(TEXT("position"), pExMonster_position); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_position->aliasID, pExMonster_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(position / 40000).");

	Property* pExMonster_direction = new Property();
	pExMonster_direction->name = TEXT("direction");
	pExMonster_direction->properUtype = 40001;
	pExMonster_direction->properFlags = 4;
	pExMonster_direction->aliasID = 2;
	KBVar* pExMonster_direction_defval = new KBVar(FVector());
	pExMonster_direction->pDefaultVal = pExMonster_direction_defval;
	pExMonsterModule->propertys.Add(TEXT("direction"), pExMonster_direction); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_direction->aliasID, pExMonster_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(direction / 40001).");

	Property* pExMonster_spaceID = new Property();
	pExMonster_spaceID->name = TEXT("spaceID");
	pExMonster_spaceID->properUtype = 40002;
	pExMonster_spaceID->properFlags = 16;
	pExMonster_spaceID->aliasID = 3;
	KBVar* pExMonster_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExMonster_spaceID->pDefaultVal = pExMonster_spaceID_defval;
	pExMonsterModule->propertys.Add(TEXT("spaceID"), pExMonster_spaceID); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_spaceID->aliasID, pExMonster_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(spaceID / 40002).");

	Property* pExMonster_BaseHP = new Property();
	pExMonster_BaseHP->name = TEXT("BaseHP");
	pExMonster_BaseHP->properUtype = 24;
	pExMonster_BaseHP->properFlags = 4;
	pExMonster_BaseHP->aliasID = 4;
	KBVar* pExMonster_BaseHP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pExMonster_BaseHP->pDefaultVal = pExMonster_BaseHP_defval;
	pExMonsterModule->propertys.Add(TEXT("BaseHP"), pExMonster_BaseHP); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_BaseHP->aliasID, pExMonster_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(BaseHP / 24).");

	Property* pExMonster_Defense = new Property();
	pExMonster_Defense->name = TEXT("Defense");
	pExMonster_Defense->properUtype = 26;
	pExMonster_Defense->properFlags = 16;
	pExMonster_Defense->aliasID = 5;
	KBVar* pExMonster_Defense_defval = new KBVar((int32)FCString::Atoi64(TEXT("10")));
	pExMonster_Defense->pDefaultVal = pExMonster_Defense_defval;
	pExMonsterModule->propertys.Add(TEXT("Defense"), pExMonster_Defense); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_Defense->aliasID, pExMonster_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(Defense / 26).");

	Property* pExMonster_HP = new Property();
	pExMonster_HP->name = TEXT("HP");
	pExMonster_HP->properUtype = 25;
	pExMonster_HP->properFlags = 4;
	pExMonster_HP->aliasID = 6;
	KBVar* pExMonster_HP_defval = new KBVar((int32)FCString::Atoi64(TEXT("500")));
	pExMonster_HP->pDefaultVal = pExMonster_HP_defval;
	pExMonsterModule->propertys.Add(TEXT("HP"), pExMonster_HP); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_HP->aliasID, pExMonster_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(HP / 25).");

	Property* pExMonster_Name = new Property();
	pExMonster_Name->name = TEXT("Name");
	pExMonster_Name->properUtype = 22;
	pExMonster_Name->properFlags = 4;
	pExMonster_Name->aliasID = 7;
	KBVar* pExMonster_Name_defval = new KBVar(FString());
	pExMonster_Name->pDefaultVal = pExMonster_Name_defval;
	pExMonsterModule->propertys.Add(TEXT("Name"), pExMonster_Name); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_Name->aliasID, pExMonster_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(Name / 22).");

	Property* pExMonster_PowerRatio = new Property();
	pExMonster_PowerRatio->name = TEXT("PowerRatio");
	pExMonster_PowerRatio->properUtype = 27;
	pExMonster_PowerRatio->properFlags = 16;
	pExMonster_PowerRatio->aliasID = 8;
	KBVar* pExMonster_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pExMonster_PowerRatio->pDefaultVal = pExMonster_PowerRatio_defval;
	pExMonsterModule->propertys.Add(TEXT("PowerRatio"), pExMonster_PowerRatio); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_PowerRatio->aliasID, pExMonster_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(PowerRatio / 27).");

	Property* pExMonster_RoleType = new Property();
	pExMonster_RoleType->name = TEXT("RoleType");
	pExMonster_RoleType->properUtype = 23;
	pExMonster_RoleType->properFlags = 4;
	pExMonster_RoleType->aliasID = 9;
	KBVar* pExMonster_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pExMonster_RoleType->pDefaultVal = pExMonster_RoleType_defval;
	pExMonsterModule->propertys.Add(TEXT("RoleType"), pExMonster_RoleType); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_RoleType->aliasID, pExMonster_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(RoleType / 23).");

	Property* pExMonster_SpeedRatio = new Property();
	pExMonster_SpeedRatio->name = TEXT("SpeedRatio");
	pExMonster_SpeedRatio->properUtype = 28;
	pExMonster_SpeedRatio->properFlags = 16;
	pExMonster_SpeedRatio->aliasID = 10;
	KBVar* pExMonster_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pExMonster_SpeedRatio->pDefaultVal = pExMonster_SpeedRatio_defval;
	pExMonsterModule->propertys.Add(TEXT("SpeedRatio"), pExMonster_SpeedRatio); 

	pExMonsterModule->usePropertyDescrAlias = true;
	pExMonsterModule->idpropertys.Add((uint16)pExMonster_SpeedRatio->aliasID, pExMonster_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), property(SpeedRatio / 28).");

	TArray<DATATYPE_BASE*> ExMonster_OnAnimUpdate_args;
	ExMonster_OnAnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pExMonster_OnAnimUpdate = new Method();
	pExMonster_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pExMonster_OnAnimUpdate->methodUtype = 46;
	pExMonster_OnAnimUpdate->aliasID = 1;
	pExMonster_OnAnimUpdate->args = ExMonster_OnAnimUpdate_args;

	pExMonsterModule->methods.Add(TEXT("OnAnimUpdate"), pExMonster_OnAnimUpdate); 
	pExMonsterModule->useMethodDescrAlias = true;
	pExMonsterModule->idmethods.Add((uint16)pExMonster_OnAnimUpdate->aliasID, pExMonster_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), method(OnAnimUpdate / 46).");

	TArray<DATATYPE_BASE*> ExMonster_OnAttack_args;

	Method* pExMonster_OnAttack = new Method();
	pExMonster_OnAttack->name = TEXT("OnAttack");
	pExMonster_OnAttack->methodUtype = 44;
	pExMonster_OnAttack->aliasID = 2;
	pExMonster_OnAttack->args = ExMonster_OnAttack_args;

	pExMonsterModule->methods.Add(TEXT("OnAttack"), pExMonster_OnAttack); 
	pExMonsterModule->useMethodDescrAlias = true;
	pExMonsterModule->idmethods.Add((uint16)pExMonster_OnAttack->aliasID, pExMonster_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), method(OnAttack / 44).");

	TArray<DATATYPE_BASE*> ExMonster_AnimUpdate_args;
	ExMonster_AnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pExMonster_AnimUpdate = new Method();
	pExMonster_AnimUpdate->name = TEXT("AnimUpdate");
	pExMonster_AnimUpdate->methodUtype = 45;
	pExMonster_AnimUpdate->aliasID = -1;
	pExMonster_AnimUpdate->args = ExMonster_AnimUpdate_args;

	pExMonsterModule->methods.Add(TEXT("AnimUpdate"), pExMonster_AnimUpdate); 
	pExMonsterModule->cell_methods.Add(TEXT("AnimUpdate"), pExMonster_AnimUpdate);

	pExMonsterModule->idcell_methods.Add(pExMonster_AnimUpdate->methodUtype, pExMonster_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), method(AnimUpdate / 45).");

	TArray<DATATYPE_BASE*> ExMonster_Attack_args;
	ExMonster_Attack_args.Add(EntityDef::id2datatypes[34]);

	Method* pExMonster_Attack = new Method();
	pExMonster_Attack->name = TEXT("Attack");
	pExMonster_Attack->methodUtype = 38;
	pExMonster_Attack->aliasID = -1;
	pExMonster_Attack->args = ExMonster_Attack_args;

	pExMonsterModule->methods.Add(TEXT("Attack"), pExMonster_Attack); 
	pExMonsterModule->cell_methods.Add(TEXT("Attack"), pExMonster_Attack);

	pExMonsterModule->idcell_methods.Add(pExMonster_Attack->methodUtype, pExMonster_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), method(Attack / 38).");

	TArray<DATATYPE_BASE*> ExMonster_Relive_args;

	Method* pExMonster_Relive = new Method();
	pExMonster_Relive->name = TEXT("Relive");
	pExMonster_Relive->methodUtype = 39;
	pExMonster_Relive->aliasID = -1;
	pExMonster_Relive->args = ExMonster_Relive_args;

	pExMonsterModule->methods.Add(TEXT("Relive"), pExMonster_Relive); 
	pExMonsterModule->cell_methods.Add(TEXT("Relive"), pExMonster_Relive);

	pExMonsterModule->idcell_methods.Add(pExMonster_Relive->methodUtype, pExMonster_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExMonster), method(Relive / 39).");

	ScriptModule* pExSkillModule = new ScriptModule("ExSkill", 6);
	EntityDef::moduledefs.Add(TEXT("ExSkill"), pExSkillModule);
	EntityDef::idmoduledefs.Add(6, pExSkillModule);

	Property* pExSkill_position = new Property();
	pExSkill_position->name = TEXT("position");
	pExSkill_position->properUtype = 40000;
	pExSkill_position->properFlags = 4;
	pExSkill_position->aliasID = 1;
	KBVar* pExSkill_position_defval = new KBVar(FVector());
	pExSkill_position->pDefaultVal = pExSkill_position_defval;
	pExSkillModule->propertys.Add(TEXT("position"), pExSkill_position); 

	pExSkillModule->usePropertyDescrAlias = true;
	pExSkillModule->idpropertys.Add((uint16)pExSkill_position->aliasID, pExSkill_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExSkill), property(position / 40000).");

	Property* pExSkill_direction = new Property();
	pExSkill_direction->name = TEXT("direction");
	pExSkill_direction->properUtype = 40001;
	pExSkill_direction->properFlags = 4;
	pExSkill_direction->aliasID = 2;
	KBVar* pExSkill_direction_defval = new KBVar(FVector());
	pExSkill_direction->pDefaultVal = pExSkill_direction_defval;
	pExSkillModule->propertys.Add(TEXT("direction"), pExSkill_direction); 

	pExSkillModule->usePropertyDescrAlias = true;
	pExSkillModule->idpropertys.Add((uint16)pExSkill_direction->aliasID, pExSkill_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExSkill), property(direction / 40001).");

	Property* pExSkill_spaceID = new Property();
	pExSkill_spaceID->name = TEXT("spaceID");
	pExSkill_spaceID->properUtype = 40002;
	pExSkill_spaceID->properFlags = 16;
	pExSkill_spaceID->aliasID = 3;
	KBVar* pExSkill_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExSkill_spaceID->pDefaultVal = pExSkill_spaceID_defval;
	pExSkillModule->propertys.Add(TEXT("spaceID"), pExSkill_spaceID); 

	pExSkillModule->usePropertyDescrAlias = true;
	pExSkillModule->idpropertys.Add((uint16)pExSkill_spaceID->aliasID, pExSkill_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExSkill), property(spaceID / 40002).");

	Property* pExSkill_SkillId = new Property();
	pExSkill_SkillId->name = TEXT("SkillId");
	pExSkill_SkillId->properUtype = 37;
	pExSkill_SkillId->properFlags = 4;
	pExSkill_SkillId->aliasID = 4;
	KBVar* pExSkill_SkillId_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pExSkill_SkillId->pDefaultVal = pExSkill_SkillId_defval;
	pExSkillModule->propertys.Add(TEXT("SkillId"), pExSkill_SkillId); 

	pExSkillModule->usePropertyDescrAlias = true;
	pExSkillModule->idpropertys.Add((uint16)pExSkill_SkillId->aliasID, pExSkill_SkillId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExSkill), property(SkillId / 37).");

	pExSkillModule->useMethodDescrAlias = true;
	ScriptModule* pExFlobModule = new ScriptModule("ExFlob", 7);
	EntityDef::moduledefs.Add(TEXT("ExFlob"), pExFlobModule);
	EntityDef::idmoduledefs.Add(7, pExFlobModule);

	Property* pExFlob_position = new Property();
	pExFlob_position->name = TEXT("position");
	pExFlob_position->properUtype = 40000;
	pExFlob_position->properFlags = 4;
	pExFlob_position->aliasID = 1;
	KBVar* pExFlob_position_defval = new KBVar(FVector());
	pExFlob_position->pDefaultVal = pExFlob_position_defval;
	pExFlobModule->propertys.Add(TEXT("position"), pExFlob_position); 

	pExFlobModule->usePropertyDescrAlias = true;
	pExFlobModule->idpropertys.Add((uint16)pExFlob_position->aliasID, pExFlob_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExFlob), property(position / 40000).");

	Property* pExFlob_direction = new Property();
	pExFlob_direction->name = TEXT("direction");
	pExFlob_direction->properUtype = 40001;
	pExFlob_direction->properFlags = 4;
	pExFlob_direction->aliasID = 2;
	KBVar* pExFlob_direction_defval = new KBVar(FVector());
	pExFlob_direction->pDefaultVal = pExFlob_direction_defval;
	pExFlobModule->propertys.Add(TEXT("direction"), pExFlob_direction); 

	pExFlobModule->usePropertyDescrAlias = true;
	pExFlobModule->idpropertys.Add((uint16)pExFlob_direction->aliasID, pExFlob_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExFlob), property(direction / 40001).");

	Property* pExFlob_spaceID = new Property();
	pExFlob_spaceID->name = TEXT("spaceID");
	pExFlob_spaceID->properUtype = 40002;
	pExFlob_spaceID->properFlags = 16;
	pExFlob_spaceID->aliasID = 3;
	KBVar* pExFlob_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExFlob_spaceID->pDefaultVal = pExFlob_spaceID_defval;
	pExFlobModule->propertys.Add(TEXT("spaceID"), pExFlob_spaceID); 

	pExFlobModule->usePropertyDescrAlias = true;
	pExFlobModule->idpropertys.Add((uint16)pExFlob_spaceID->aliasID, pExFlob_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExFlob), property(spaceID / 40002).");

	Property* pExFlob_GoodId = new Property();
	pExFlob_GoodId->name = TEXT("GoodId");
	pExFlob_GoodId->properUtype = 43;
	pExFlob_GoodId->properFlags = 4;
	pExFlob_GoodId->aliasID = 4;
	KBVar* pExFlob_GoodId_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pExFlob_GoodId->pDefaultVal = pExFlob_GoodId_defval;
	pExFlobModule->propertys.Add(TEXT("GoodId"), pExFlob_GoodId); 

	pExFlobModule->usePropertyDescrAlias = true;
	pExFlobModule->idpropertys.Add((uint16)pExFlob_GoodId->aliasID, pExFlob_GoodId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExFlob), property(GoodId / 43).");

	pExFlobModule->useMethodDescrAlias = true;
	ScriptModule* pExGateModule = new ScriptModule("ExGate", 8);
	EntityDef::moduledefs.Add(TEXT("ExGate"), pExGateModule);
	EntityDef::idmoduledefs.Add(8, pExGateModule);

	Property* pExGate_position = new Property();
	pExGate_position->name = TEXT("position");
	pExGate_position->properUtype = 40000;
	pExGate_position->properFlags = 4;
	pExGate_position->aliasID = 1;
	KBVar* pExGate_position_defval = new KBVar(FVector());
	pExGate_position->pDefaultVal = pExGate_position_defval;
	pExGateModule->propertys.Add(TEXT("position"), pExGate_position); 

	pExGateModule->usePropertyDescrAlias = true;
	pExGateModule->idpropertys.Add((uint16)pExGate_position->aliasID, pExGate_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExGate), property(position / 40000).");

	Property* pExGate_direction = new Property();
	pExGate_direction->name = TEXT("direction");
	pExGate_direction->properUtype = 40001;
	pExGate_direction->properFlags = 4;
	pExGate_direction->aliasID = 2;
	KBVar* pExGate_direction_defval = new KBVar(FVector());
	pExGate_direction->pDefaultVal = pExGate_direction_defval;
	pExGateModule->propertys.Add(TEXT("direction"), pExGate_direction); 

	pExGateModule->usePropertyDescrAlias = true;
	pExGateModule->idpropertys.Add((uint16)pExGate_direction->aliasID, pExGate_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExGate), property(direction / 40001).");

	Property* pExGate_spaceID = new Property();
	pExGate_spaceID->name = TEXT("spaceID");
	pExGate_spaceID->properUtype = 40002;
	pExGate_spaceID->properFlags = 16;
	pExGate_spaceID->aliasID = 3;
	KBVar* pExGate_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pExGate_spaceID->pDefaultVal = pExGate_spaceID_defval;
	pExGateModule->propertys.Add(TEXT("spaceID"), pExGate_spaceID); 

	pExGateModule->usePropertyDescrAlias = true;
	pExGateModule->idpropertys.Add((uint16)pExGate_spaceID->aliasID, pExGate_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExGate), property(spaceID / 40002).");

	Property* pExGate_RoomId = new Property();
	pExGate_RoomId->name = TEXT("RoomId");
	pExGate_RoomId->properUtype = 47;
	pExGate_RoomId->properFlags = 4;
	pExGate_RoomId->aliasID = 4;
	KBVar* pExGate_RoomId_defval = new KBVar((uint64)FCString::Atoi64(TEXT("")));
	pExGate_RoomId->pDefaultVal = pExGate_RoomId_defval;
	pExGateModule->propertys.Add(TEXT("RoomId"), pExGate_RoomId); 

	pExGateModule->usePropertyDescrAlias = true;
	pExGateModule->idpropertys.Add((uint16)pExGate_RoomId->aliasID, pExGate_RoomId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExGate), property(RoomId / 47).");

	Property* pExGate_RoomName = new Property();
	pExGate_RoomName->name = TEXT("RoomName");
	pExGate_RoomName->properUtype = 48;
	pExGate_RoomName->properFlags = 4;
	pExGate_RoomName->aliasID = 5;
	KBVar* pExGate_RoomName_defval = new KBVar(FString());
	pExGate_RoomName->pDefaultVal = pExGate_RoomName_defval;
	pExGateModule->propertys.Add(TEXT("RoomName"), pExGate_RoomName); 

	pExGateModule->usePropertyDescrAlias = true;
	pExGateModule->idpropertys.Add((uint16)pExGate_RoomName->aliasID, pExGate_RoomName);

	//DEBUG_MSG("EntityDef::initScriptModules: add(ExGate), property(RoomName / 48).");

	pExGateModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("KIND_ID");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("DBID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("ENTITY_ID");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("VECTOR3");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("ENTITY_LIST");
		DATATYPE_ENTITY_LIST* pDatatype = new DATATYPE_ENTITY_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ROLE_DATA");
		DATATYPE_ROLE_DATA* pDatatype = new DATATYPE_ROLE_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("ROLE_INFO");
		DATATYPE_ROLE_INFO* pDatatype = new DATATYPE_ROLE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 25;
		FString typeName = TEXT("ROLE_LIST");
		DATATYPE_ROLE_LIST* pDatatype = new DATATYPE_ROLE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 27;
		FString typeName = TEXT("ROOM_INFO");
		DATATYPE_ROOM_INFO* pDatatype = new DATATYPE_ROOM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 28;
		FString typeName = TEXT("ROOM_LIST");
		DATATYPE_ROOM_LIST* pDatatype = new DATATYPE_ROOM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 30;
		FString typeName = TEXT("ANIM_INFO");
		DATATYPE_ANIM_INFO* pDatatype = new DATATYPE_ANIM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 31;
		FString typeName = TEXT("GOOD_INFO");
		DATATYPE_GOOD_INFO* pDatatype = new DATATYPE_GOOD_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 32;
		FString typeName = TEXT("BAG_INFO");
		DATATYPE_BAG_INFO* pDatatype = new DATATYPE_BAG_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 34;
		FString typeName = TEXT("SKILL_INFO");
		DATATYPE_SKILL_INFO* pDatatype = new DATATYPE_SKILL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 35;
		FString typeName = TEXT("CHAT_INFO");
		DATATYPE_CHAT_INFO* pDatatype = new DATATYPE_CHAT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 36;
		FString typeName = TEXT("CHAT_LIST");
		DATATYPE_CHAT_LIST* pDatatype = new DATATYPE_CHAT_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}