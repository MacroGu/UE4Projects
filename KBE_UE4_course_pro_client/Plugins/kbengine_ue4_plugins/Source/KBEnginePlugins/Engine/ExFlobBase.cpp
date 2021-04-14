#include "ExFlobBase.h"
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



void ExFlobBase::onComponentsEnterworld()
{
}

void ExFlobBase::onComponentsLeaveworld()
{
}

void ExFlobBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_ExFlobBase(id(), className());
}

void ExFlobBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_ExFlobBase(id(), className());
}

void ExFlobBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* ExFlobBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* ExFlobBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void ExFlobBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void ExFlobBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("ExFlob");

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
			case 43:
			{
				uint8 oldval_GoodId = GoodId;
				GoodId = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onGoodIdChanged(oldval_GoodId);
				}
				else
				{
					if(inWorld())
						onGoodIdChanged(oldval_GoodId);
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

void ExFlobBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["ExFlob"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint8 oldval_GoodId = GoodId;
	Property* pProp_GoodId = pdatas[4];
	if(pProp_GoodId->isBase())
	{
		if(inited() && !inWorld())
			onGoodIdChanged(oldval_GoodId);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_GoodId->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onGoodIdChanged(oldval_GoodId);
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

ExFlobBase::ExFlobBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	GoodId((uint8)FCString::Atoi64(TEXT("0")))
{
}

ExFlobBase::~ExFlobBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void ExFlobBase::attachComponents()
{
}

void ExFlobBase::detachComponents()
{
}

}