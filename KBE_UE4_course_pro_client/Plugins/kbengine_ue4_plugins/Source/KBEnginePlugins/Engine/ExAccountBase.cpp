#include "ExAccountBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void ExAccountBase::onComponentsEnterworld()
{
}

void ExAccountBase::onComponentsLeaveworld()
{
}

void ExAccountBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_ExAccountBase(id(), className());
}

void ExAccountBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_ExAccountBase(id(), className());
}

void ExAccountBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* ExAccountBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* ExAccountBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void ExAccountBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("ExAccount");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 9:
		{
			uint8 OnCreateRole_arg1 = stream.readUint8();
			ROLE_INFO OnCreateRole_arg2;
			((DATATYPE_ROLE_INFO*)pMethod->args[1])->createFromStreamEx(stream, OnCreateRole_arg2);
			OnCreateRole(OnCreateRole_arg1, OnCreateRole_arg2);
			break;
		}
		case 13:
		{
			uint8 OnCreateRoom_arg1 = stream.readUint8();
			ROOM_INFO OnCreateRoom_arg2;
			((DATATYPE_ROOM_INFO*)pMethod->args[1])->createFromStreamEx(stream, OnCreateRoom_arg2);
			OnCreateRoom(OnCreateRoom_arg1, OnCreateRoom_arg2);
			break;
		}
		case 10:
		{
			uint64 OnRemoveRole_arg1 = stream.readUint64();
			OnRemoveRole(OnRemoveRole_arg1);
			break;
		}
		case 8:
		{
			ROLE_LIST OnReqRoleList_arg1;
			((DATATYPE_ROLE_LIST*)pMethod->args[0])->createFromStreamEx(stream, OnReqRoleList_arg1);
			OnReqRoleList(OnReqRoleList_arg1);
			break;
		}
		case 12:
		{
			ROOM_LIST OnReqRoomList_arg1;
			((DATATYPE_ROOM_LIST*)pMethod->args[0])->createFromStreamEx(stream, OnReqRoomList_arg1);
			OnReqRoomList(OnReqRoomList_arg1);
			break;
		}
		case 11:
		{
			uint8 OnSelectRoleGame_arg1 = stream.readUint8();
			uint64 OnSelectRoleGame_arg2 = stream.readUint64();
			OnSelectRoleGame(OnSelectRoleGame_arg1, OnSelectRoleGame_arg2);
			break;
		}
		default:
			break;
	};
}

void ExAccountBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("ExAccount");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 2:
			{
				uint64 oldval_LastSelRole = LastSelRole;
				LastSelRole = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onLastSelRoleChanged(oldval_LastSelRole);
				}
				else
				{
					if(inWorld())
						onLastSelRoleChanged(oldval_LastSelRole);
				}

				break;
			}
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void ExAccountBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["ExAccount"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint64 oldval_LastSelRole = LastSelRole;
	Property* pProp_LastSelRole = pdatas[4];
	if(pProp_LastSelRole->isBase())
	{
		if(inited() && !inWorld())
			onLastSelRoleChanged(oldval_LastSelRole);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_LastSelRole->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onLastSelRoleChanged(oldval_LastSelRole);
			}
		}
	}

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

ExAccountBase::ExAccountBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	LastSelRole((uint64)FCString::Atoi64(TEXT("0")))
{
}

ExAccountBase::~ExAccountBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void ExAccountBase::attachComponents()
{
}

void ExAccountBase::detachComponents()
{
}

}