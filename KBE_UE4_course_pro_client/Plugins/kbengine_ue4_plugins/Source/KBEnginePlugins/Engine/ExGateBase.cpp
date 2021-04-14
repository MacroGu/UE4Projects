#include "ExGateBase.h"
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



void ExGateBase::onComponentsEnterworld()
{
}

void ExGateBase::onComponentsLeaveworld()
{
}

void ExGateBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_ExGateBase(id(), className());
}

void ExGateBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_ExGateBase(id(), className());
}

void ExGateBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* ExGateBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* ExGateBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void ExGateBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void ExGateBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("ExGate");

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
			case 47:
			{
				uint64 oldval_RoomId = RoomId;
				RoomId = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onRoomIdChanged(oldval_RoomId);
				}
				else
				{
					if(inWorld())
						onRoomIdChanged(oldval_RoomId);
				}

				break;
			}
			case 48:
			{
				FString oldval_RoomName = RoomName;
				RoomName = stream.readUnicode();

				if(pProp->isBase())
				{
					if(inited())
						onRoomNameChanged(oldval_RoomName);
				}
				else
				{
					if(inWorld())
						onRoomNameChanged(oldval_RoomName);
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

void ExGateBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["ExGate"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint64 oldval_RoomId = RoomId;
	Property* pProp_RoomId = pdatas[4];
	if(pProp_RoomId->isBase())
	{
		if(inited() && !inWorld())
			onRoomIdChanged(oldval_RoomId);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_RoomId->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onRoomIdChanged(oldval_RoomId);
			}
		}
	}

	FString oldval_RoomName = RoomName;
	Property* pProp_RoomName = pdatas[5];
	if(pProp_RoomName->isBase())
	{
		if(inited() && !inWorld())
			onRoomNameChanged(oldval_RoomName);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_RoomName->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onRoomNameChanged(oldval_RoomName);
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

ExGateBase::ExGateBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	RoomId((uint64)FCString::Atoi64(TEXT("0"))),
	RoomName(TEXT(""))
{
}

ExGateBase::~ExGateBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void ExGateBase::attachComponents()
{
}

void ExGateBase::detachComponents()
{
}

}