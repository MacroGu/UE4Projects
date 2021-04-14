// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/ExMmoGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Player/ExPlayerCharacter.h"
#include "Player/ExMmoController.h"
#include "Player/ExRemoteCharacter.h"
#include "Scripts/ExCommon.h"
#include "Scripts/ExRole.h"
#include "Scripts/ExMonster.h"
#include "Scripts/ExEventData.h"
#include <Kismet/GameplayStatics.h>
#include "HUD/ExMmoWidget.h"
#include "Center/ExGameInstance.h"
#include "Player/ExMonsterCharacter.h"
#include "Scene/ExSkillActor.h"
#include "Scripts/ExSkill.h"
#include "Scripts/ExFlob.h"
#include "Scene/ExFlobActor.h"
#include <Scripts/ExGate.h>
#include "../Scene/ExGateActor.h"




void AExMmoGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, OnEnterWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, OnLeaveWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, OnEnterSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, OnLeaveSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, SetPosition);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, SetDirection);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, UpdatePosition);

	KBENGINE_REGISTER_EVENT("OnAnimUpdate", OnAnimUpdate);
	KBENGINE_REGISTER_EVENT("SetBaseHP", SetBaseHP);
	KBENGINE_REGISTER_EVENT("SetHP", SetHP);
	KBENGINE_REGISTER_EVENT("OnAttack", OnAttack);
	KBENGINE_REGISTER_EVENT("SetDefense", SetDefense);
	KBENGINE_REGISTER_EVENT("SetPowerRatio", SetPowerRatio);
	KBENGINE_REGISTER_EVENT("SetSpeedRatio", SetSpeedRatio);

	// 这个事件用于离开房间
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLeaveRoom);

	// 这个事件触发时我们需要切换地图到游戏世界地图
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);

}

void AExMmoGameMode::BeginPlay()
{
	//获取 GameInstance
	UExGameInstance* GameInstance = Cast<UExGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// 创建UI
	MmoWidget = CreateWidget<UExMmoWidget>(GetWorld(), MmoWidgetClass);
	MmoWidget->AddToViewport();
	// 注册KBE事件以及设置房间名
	MmoWidget->InstallEvents(GameInstance->RoomName);

	Super::BeginPlay();

	check(KBEngine::KBEngineApp::getSingleton().isInitialized());

	// 此时我们需要再次触发一次onEnterWorld，让表现层能够在游戏场景中创建出所有的实体
	KBEngine::KBEngineApp::ENTITIES_MAP& EntitiesMap = KBEngine::KBEngineApp::getSingleton().entities();
	for (auto& EntityItem : EntitiesMap)
	{
		KBEngine::Entity* EntityInst = EntityItem.Value;

		UKBEventData_onEnterWorld* EventData = NewObject<UKBEventData_onEnterWorld>();
		EventData->entityID = EntityInst->id();
		EventData->spaceID = KBEngine::KBEngineApp::getSingleton().spaceID();
		KBPos2UE4Pos(EventData->position, EntityInst->position);
		EventData->direction = EntityInst->direction;
		EventData->moveSpeed = EntityInst->velocity();
		EventData->isOnGround = EntityInst->isOnGround();
		EventData->isPlayer = EntityInst->isPlayer();
		EventData->entityClassName = EntityInst->className();
		EventData->res = TEXT("");
		KBENGINE_EVENT_FIRE(KBEngine::KBEventTypes::onEnterWorld, EventData);
	}

	// 请求背包列表
	KBENGINE_EVENT_FIRE("ReqBagList", NewObject<UKBEventData>());

}

void AExMmoGameMode::OnEnterWorld(const UKBEventData* EventData)
{

	const UKBEventData_onEnterWorld* ServerData = Cast<UKBEventData_onEnterWorld>(EventData);

	// 根据实体ID获取实体的实例
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(ServerData->entityID);

	// 获取旋转
	FRotator Rotator(0.f, 0.f, 0.f);
	KBDir2UE4Dir(Rotator, ServerData->direction);

	// 区分类型生成UE4 对象
	if (ServerData->isPlayer)
	{
		//  强转实体类型为ExRole
		KBEngine::ExRole* RoleInst = static_cast<KBEngine::ExRole*>(EntityInst);
		FTransform SpawnTransform(Rotator, RoleInst->SpawnPoint);
		PlayerCharacter = Cast<AExPlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerClassList[RoleInst->RoleType], SpawnTransform));
		if (PlayerCharacter)
		{
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->MmoGameMode = this;
			PlayerCharacter->MmoWidget = MmoWidget;
			PlayerCharacter->RoleType = RoleInst->RoleType;
			PlayerCharacter->RoleName = RoleInst->Name;
			PlayerCharacter->IsPlayer = true;

			// 创建出角色, 需要绑定到Controller
			AExMmoController* MmoController = Cast<AExMmoController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			PlayerCharacter->MmoController = MmoController;
			MmoWidget->SetName(RoleInst->Name);
			MmoWidget->PlayerCharacter = PlayerCharacter;

			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);
			if (MmoController)
			{
				MmoController->Possess(PlayerCharacter);
			}
		}
	}
	else
	{
		// 获取生成位置
		FTransform SpawnTransform(Rotator, ServerData->position);
		// 远程玩家， 怪物， 技能， 掉落物，传送门
		if (ServerData->entityClassName.Equals(FString("ExRole")))
		{
			// 强转实体类型为ExRole
			KBEngine::ExRole* RoleInst = static_cast<KBEngine::ExRole*>(EntityInst);

			// 生成远程玩家
			AExRemoteCharacter* RemoteCharacter = Cast<AExRemoteCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RemoteClassList[RoleInst->RoleType], SpawnTransform));
			if (RemoteCharacter)
			{
				RemoteCharacter->EntityId = ServerData->entityID;
				RemoteCharacter->MmoGameMode = this;
				RemoteCharacter->RoleType = RoleInst->RoleType;
				RemoteCharacter->RoleName = RoleInst->Name;
				RemoteCharacter->IsPlayer = false;

				UGameplayStatics::FinishSpawningActor(RemoteCharacter, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("ExMonster")))
		{
			// 强转实体类型为ExMonster
			KBEngine::ExMonster* MonsterInst = static_cast<KBEngine::ExMonster*>(EntityInst);

			// 生成怪物
			AExMonsterCharacter* MonsterCharacter = Cast<AExMonsterCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MonsterClass, SpawnTransform));
			if (MonsterCharacter)
			{
				MonsterCharacter->EntityId = ServerData->entityID;
				MonsterCharacter->MmoGameMode = this;
				MonsterCharacter->RoleName = MonsterInst->Name;

				UGameplayStatics::FinishSpawningActor(MonsterCharacter, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("ExSkill")))
		{
			// 获取ExSkill的实体
			KBEngine::ExSkill* SkillInst = static_cast<KBEngine::ExSkill*>(EntityInst);

			// 生成对象
			AExSkillActor* SkillActor = Cast<AExSkillActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SkillClassList[SkillInst->SkillId], SpawnTransform));
			if (SkillActor)
			{
				SkillActor->MmoGameMode = this;
				SkillActor->EntityId = ServerData->entityID;
				SkillActor->SkillId = SkillInst->SkillId;

				UGameplayStatics::FinishSpawningActor(SkillActor, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("ExFlob")))
		{
			// 获取ExFlob的实体
			KBEngine::ExFlob* FlobInst = static_cast<KBEngine::ExFlob*>(EntityInst);

			// 生成对象
			AExFlobActor* FlobActor = Cast<AExFlobActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, FlobClass, SpawnTransform));
			if (FlobActor)
			{
				FlobActor->MmoGameMode = this;
				FlobActor->EntityId = ServerData->entityID;
				FlobActor->GoodId = FlobInst->GoodId;

				UGameplayStatics::FinishSpawningActor(FlobActor, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("ExGate")))
		{
			// 获取ExGate的实体
			KBEngine::ExGate* GateInst = static_cast<KBEngine::ExGate*>(EntityInst);

			// 生成对象
			GateActor = Cast<AExGateActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, GateClass, SpawnTransform));
			if (GateActor)
			{
				GateActor->EntityId = ServerData->entityID;
				GateActor->RoomId = GateInst->RoomId;
				GateActor->RoomName = GateInst->RoomName;

				UGameplayStatics::FinishSpawningActor(GateActor, SpawnTransform);
			}
		}
	}
}

void AExMmoGameMode::OnLeaveWorld(const UKBEventData* EventData)
{
	const UKBEventData_onLeaveWorld* ServerData = Cast<UKBEventData_onLeaveWorld>(EventData);

	// 如果存在于CharacterMap，说明不是本地玩家
	if (CharacterMap.Contains(ServerData->entityID))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);

		// 根据实体ID 获取实体对象
		KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(ServerData->entityID);

		// 远程玩家
		if (EntityInst->className().Equals(FString("ExRole")))
		{
			// 直接销毁远程玩家
			CharacterEntity->Destroy();
		}
		else if (EntityInst->className().Equals(FString("ExMonster")))
		{
			AExMonsterCharacter* MonsterCharacter = Cast<AExMonsterCharacter>(CharacterEntity);
			MonsterCharacter->PlayDeath();
		}
	}
	else if(SkillMap.Contains(ServerData->entityID))
	{
		AExSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->PlayExplode();
	}
	else if (FlobMap.Contains(ServerData->entityID))
	{
		AExFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->Destroy();
	}
}

void AExMmoGameMode::OnEnterSpace(const UKBEventData* EventData)
{

}

void AExMmoGameMode::OnLeaveSpace(const UKBEventData* EventData)
{

}

void AExMmoGameMode::SetPosition(const UKBEventData* EventData)
{
	const UKBEventData_set_position* ServerData = Cast<UKBEventData_set_position>(EventData);

	if (CharacterMap.Contains(ServerData->entityID))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetActorLocation(ServerData->position);
		CharacterEntity->SetTargetPosition(ServerData->position);
	}

	if (SkillMap.Contains(ServerData->entityID))
	{
		AExSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetActorLocation(ServerData->position);
		SkillActor->SetTargetPosition(ServerData->position);
	}

	if (FlobMap.Contains(ServerData->entityID))
	{
		AExFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetActorLocation(ServerData->position);
		FlobActor->SetTargetPosition(ServerData->position);
	}
}

void AExMmoGameMode::SetDirection(const UKBEventData* EventData)
{
	const UKBEventData_set_direction* ServerData = Cast<UKBEventData_set_direction>(EventData);

	if (CharacterMap.Contains(ServerData->entityID))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetActorRotation(ServerData->direction);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}

	if (SkillMap.Contains(ServerData->entityID))
	{
		AExSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetActorRotation(ServerData->direction);
	}

	if (FlobMap.Contains(ServerData->entityID))
	{
		AExFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetActorRotation(ServerData->direction);
	}

}

void AExMmoGameMode::UpdatePosition(const UKBEventData* EventData)
{
	const UKBEventData_updatePosition* ServerData = Cast<UKBEventData_updatePosition>(EventData);

	if (CharacterMap.Contains(ServerData->entityID))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetTargetPosition(ServerData->position);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}

	if (SkillMap.Contains(ServerData->entityID))
	{
		AExSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetTargetPosition(ServerData->position);
	}

	if (FlobMap.Contains(ServerData->entityID))
	{
		AExFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetTargetPosition(ServerData->position);
	}

}

void AExMmoGameMode::OnAnimUpdate(const UKBEventData* EventData)
{
	const UKBEventData_OnAnimUpdate* ServerData = Cast<UKBEventData_OnAnimUpdate>(EventData);

	if (CharacterMap.Contains(ServerData->EntityId))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->EntityId);
		CharacterEntity->SetTargetAnim(ServerData->Speed, ServerData->Direction);
	}

}

void AExMmoGameMode::SetBaseHP(const UKBEventData* EventData)
{
	const UKBEventData_SetBaseHP* ServerData = Cast<UKBEventData_SetBaseHP>(EventData);
	if (ServerData->IsPlayer)
	{
		if (PlayerCharacter)
		{
			PlayerCharacter->SetBaseHP(ServerData->BaseHP);

			float HpPercent = FMath::Clamp((float)PlayerCharacter->HP / (float)PlayerCharacter->BaseHP, 0.f, 1.f);
			if (MmoWidget)
			{
				MmoWidget->SetHpPercent(HpPercent);
				// 还有更新血值上限到UI
				MmoWidget->SetBaseHp(ServerData->BaseHP);
			}
		}
	}
	else
	{
		if (CharacterMap.Contains(ServerData->EntityId))
		{
			AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->EntityId);
			CharacterEntity->SetBaseHP(ServerData->BaseHP);
		}
	}

}

void AExMmoGameMode::SetHP(const UKBEventData* EventData)
{
	const UKBEventData_SetHP* ServerData = Cast<UKBEventData_SetHP>(EventData);
	if (ServerData->IsPlayer)
	{
		if (PlayerCharacter)
		{
			PlayerCharacter->SetHP(ServerData->HP);

			// 计算HP百分比
			float HpPercent = FMath::Clamp(((float)PlayerCharacter->HP / (float)PlayerCharacter->BaseHP), 0.f, 1.f);
			MmoWidget->SetHpPercent(HpPercent);
		}
	}
	else
	{
		if (CharacterMap.Contains(ServerData->EntityId))
		{
			AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->EntityId);
			CharacterEntity->SetHP(ServerData->HP);
		}
	}

}

void AExMmoGameMode::SetDefense(const UKBEventData* EventData)
{
	// 防御力只有玩家更新，防御力只更新UI显示
	const UKBEventData_SetDefense* ServerData = Cast<UKBEventData_SetDefense>(EventData);

	if (MmoWidget)
	{
		MmoWidget->SetDefense(ServerData->Defense);
	}

}

void AExMmoGameMode::SetPowerRatio(const UKBEventData* EventData)
{
	// 力量只有玩家更新，力量只更新UI显示
	const UKBEventData_SetPowerRatio* ServerData = Cast<UKBEventData_SetPowerRatio>(EventData);

	if (MmoWidget)
	{
		MmoWidget->SetPowerRatio(ServerData->PowerRatio);
	}
}

void AExMmoGameMode::SetSpeedRatio(const UKBEventData* EventData)
{
	// 速度只有玩家更新，速度只更新UI显示
	const UKBEventData_SetSpeedRatio* ServerData = Cast<UKBEventData_SetSpeedRatio>(EventData);

	// 更新到UI
	if (MmoWidget)
	{
		MmoWidget->SetSpeedRatio(ServerData->SpeedRatio);
	}

	// 更新速度到本地玩家
	if (PlayerCharacter)
	{
		PlayerCharacter->SetSpeedRatio(ServerData->SpeedRatio);
	}

}

void AExMmoGameMode::OnAttack(const UKBEventData* EventData)
{
	const UKBEventData_OnAttack* ServerData = Cast<UKBEventData_OnAttack>(EventData);

	if (ServerData->EntityId == PlayerCharacter->EntityId)
	{
		PlayerCharacter->OnAttack();
	}

	if (CharacterMap.Contains(ServerData->EntityId))
	{
		AExCharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->EntityId);
		CharacterEntity->OnAttack();
	}
}

void AExMmoGameMode::UnInstallEvent()
{
	Super::UnInstallEvent();

	MmoWidget->UnInstallEvents();

}

void AExMmoGameMode::OnLeaveRoom(const UKBEventData* EventData)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));
}

void AExMmoGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);

	FString MapName;		// MmoMapOne
	FString TempStr;
	ServerData->spaceResPath.Split("/", &TempStr, &MapName);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}
