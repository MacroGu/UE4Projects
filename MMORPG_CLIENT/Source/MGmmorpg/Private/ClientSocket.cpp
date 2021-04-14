// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Runtime/Core/Public/Templates/SharedPointer.h"
#include "Runtime/Core/Public/Templates/SharedPointerInternals.h"
#include "Runtime/Sockets/Public/IPAddress.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "MGPlayerController.h"
#include "LoginGameMode.h"
#include "LogicalDefinition.h"
#include "PlayerCharacter.h"
#include "Engine/Engine.h"






ClientSocket::ClientSocket() : SocketClient(nullptr), serverIP(""), serverPort(0), sessionID(0), isLoginSuccess(false)
{
}

ClientSocket::~ClientSocket()
{
}

bool ClientSocket::InitSocket()
{
	UE_LOG(LogTemp, Warning, TEXT("SocketCreate begin"));
	SocketClient = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	if (!SocketClient)
	{
		return false;
	}

	return true;
}

void ClientSocket::SetPlayerController(AMGPlayerController* pPlayerController)
{
	if (pPlayerController)
	{
		PlayerController = pPlayerController;
	}
}

void ClientSocket::SetCurrentGameMode(AGameModeBase* GameMode)
{
	if (GameMode)
	{
		CurrentGameMode = GameMode;
	}
}

bool ClientSocket::SendDataToServer(const uint16_t& msgID, ::google::protobuf::Message& protobufData)
{
// 	if (!SocketClient)
// 		return false;
// 
// 	uint16_t msgSize = 0;
// 	int totalSize = protobufData.ByteSize() + sizeof(msgID) + sizeof(msgSize);
// 	msgSize = totalSize - sizeof(msgSize);
// 	char* ReqData = new char[totalSize];
// 	FMemory::Memcpy(ReqData, &msgSize, sizeof(msgSize));
// 	FMemory::Memcpy(ReqData + sizeof(msgSize), &msgID, sizeof(msgID));
// 	protobufData.SerializeToArray(ReqData + sizeof(msgID) + sizeof(msgSize), protobufData.ByteSize());
// 	int32 acutalSent = 0;
// 	if (!SocketClient->Send((uint8*)ReqData, totalSize, acutalSent))
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("send login req success!"));
// 		return false;
// 	}

	return true;
}

bool ClientSocket::ConnectServer()
{
// 	FIPv4Address ip;
// 	FIPv4Address::Parse(serverIP, ip);
// 
// 	TSharedRef<FInternetAddr, ESPMode::NotThreadSafe> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
// 	addr->SetIp(ip.Value);
// 	addr->SetPort(serverPort);
// 	if (SocketClient->Connect(*addr))
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("connect to server Succ!"));
// 		return true;
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("connect to server failed!"));
// 		return false;
// 	}

	return true;
}

void ClientSocket::SetServerIPandPort(const FString& serverIP, const int32& serverPort)
{
	this->serverIP = serverIP;
	this->serverPort = serverPort;
}

bool ClientSocket::SignUp(const FText& Account, const FText& Pw)
{
// 	login::Login_RegisterAccount_Request_21000 RegisterAccountReq;
// 	RegisterAccountReq.set_accouent(TCHAR_TO_UTF8(*Account.ToString()));
// 	RegisterAccountReq.set_password(TCHAR_TO_UTF8(*Account.ToString()));
// 
// 	if (!SendDataToServer(EPacketTypeLogin::REGISTER_ACCOUNT_REQ, RegisterAccountReq))
// 		return false;
// 
// 	char	recvData[MAX_BUFFER];
// 	int32_t read = 0;
// 	SocketClient->Recv((uint8*)recvData, MAX_BUFFER, read);
// 	return SignUpRsp(recvData + sizeof(uint16_t) + sizeof(uint16_t), read - sizeof(uint16_t) - sizeof(uint16_t));
	return true;
}

bool ClientSocket::SignUpRsp(char* data, int len)
{
// 	login::Login_RegisterAccount_Response_21001 RegisterRpo;
// 	if (!RegisterRpo.ParseFromArray(data, len))
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("测试注册  请求  parse failed! "));
// 		return false;
// 	}
// 
// 	int32_t errorCode = RegisterRpo.error();
// 	if (errorCode != 0)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("注册账号 请求 失败 !  errorCode : %d "), errorCode);
// 		return false;
// 	}

	return true;
}

bool ClientSocket::Login(const FText& Account, const FText& Pw)
{
// 	login::Login_LoginServer_Request_21002 LoginServerReq;
// 	LoginServerReq.set_accouent(TCHAR_TO_UTF8(*Account.ToString()));
// 	LoginServerReq.set_password(TCHAR_TO_UTF8(*Account.ToString()));
// 	
// 	if (!SendDataToServer(EPacketTypeLogin::LOGIN_SERVER_REQ, LoginServerReq))
// 		return false;
// 
// 	char	recvData[MAX_BUFFER];
// 	int32_t read = 0;
// 	SocketClient->Recv((uint8*)recvData, MAX_BUFFER, read);
//	return LoginRsp(recvData + sizeof(uint16_t) + sizeof(uint16_t), read - sizeof(uint16_t) - sizeof(uint16_t));

	return LoginRsp(nullptr, 0);
}

bool ClientSocket::LoginRsp(char* data, int len)
{
// 	login::Login_LoginServer_Response_21003 LoginServerRpo;
// 	if (!LoginServerRpo.ParseFromArray(data, len))
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("测试登录  请求  parse failed! "));
// 		return false;
// 	}
// 
// 	int32_t errorCode = LoginServerRpo.error();
// 	if (errorCode != 0)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("登录服务器失败 !  errorCode : %d "), errorCode);
// 		return false;
// 	}
// 
// 	sessionID = LoginServerRpo.sessionid();
// 	isLoginSuccess = true;

	Cast<ALoginGameMode>(CurrentGameMode)->EnterScene();

	return true;
}


void ClientSocket::EnterScene(APlayerCharacter* CurPlayer)
{
	if (!CurPlayer)
		return;

	SceneMsg::Scene_EnterEnroll_Request_22000 CurPlayerStatus;
	SceneMsg::Struct_Player_Status* CurSelfStatus = new SceneMsg::Struct_Player_Status;
	FromPlayerCharacterToProtoStatus(CurPlayer, CurSelfStatus);
	CurSelfStatus->set_positionx(CurPlayer->GetActorLocation().X / UE4_LOCATION_TO_SERVER);
	CurSelfStatus->set_positiony(CurPlayer->GetActorLocation().Y / UE4_LOCATION_TO_SERVER);

	CurPlayerStatus.set_sessionid(CurPlayer->SessionID);
	CurPlayerStatus.set_allocated_selfstatus(CurSelfStatus);

	if (!SendDataToServer(EPacketTypeScene::ENROLL_ENTER_SCENE_REQ, CurPlayerStatus))
		return;

	// 由统一接收消息部分处理，服务器返回进入场景结果
}

void ClientSocket::EnterSceneRsp(char* data, int len)
{
	if (!PlayerController)
		return;

	SceneMsg::Scene_EnterEnroll_Response_22001 EnterSceneRpo;
	if (!EnterSceneRpo.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("enter scene msg parse failed! "));
		return;
	}

	int32_t errorCode = EnterSceneRpo.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("enter scene failed !  errorCode : %d "), errorCode);
		return;
	}

	SceneMsg::Struct_Player_Status otherPlayerStatus;
	int otherPlayerSize = EnterSceneRpo.playersstatus_size();
	for (int i = 0; i < otherPlayerSize; ++i)
	{
		otherPlayerStatus = EnterSceneRpo.playersstatus(i);
		stPlayerStatus newPlayerStatus;
		FromPlayerStatusToProtoStatus(newPlayerStatus, otherPlayerStatus);
		PlayerController->OtherPlayerEnterInsight(newPlayerStatus);
	}

	SceneMsg::Struct_Monster_Status monsterStatus;
	int monsterSize = EnterSceneRpo.monsterstatus_size();
	for (int i = 0; i < monsterSize; ++i)
	{
		monsterStatus = EnterSceneRpo.monsterstatus(i);
		stMonsterStatus newMonsterStatus;
		FromMonsterStatusToProtoStatus(newMonsterStatus, monsterStatus);
		PlayerController->UpdateOtherMonster(newMonsterStatus);
	}

}

void ClientSocket::FromPlayerCharacterToProtoStatus(APlayerCharacter* player, SceneMsg::Struct_Player_Status* protostatus)
{
	if (!player || !protostatus)
		return;

	const auto& Location = player->GetActorLocation();
	const auto& Rotation = player->GetActorRotation();
	const auto& Velocity = player->GetVelocity();

	protostatus->set_roleuid(player->SessionID);
	protostatus->set_positionx(Location.X);
	protostatus->set_positiony(Location.Y);
	protostatus->set_positionz(Location.Z);
	protostatus->set_pitch(Rotation.Pitch);
	protostatus->set_yaw(Rotation.Yaw);
	protostatus->set_roll(Rotation.Roll);
	protostatus->set_speedx(Velocity.X);
	protostatus->set_speedy(Velocity.Y);
	protostatus->set_speedz(Velocity.Z);
	protostatus->set_isattacking(player->IsAttacking);

}

void ClientSocket::FromPlayerStatusToProtoStatus(stPlayerStatus& playerstatus, const SceneMsg::Struct_Player_Status& protoPlayerStatus)
{
	playerstatus.SessionId = protoPlayerStatus.roleuid();
	playerstatus.PositionX = protoPlayerStatus.positionx() * UE4_LOCATION_TO_SERVER;
	playerstatus.PositionY = protoPlayerStatus.positiony() * UE4_LOCATION_TO_SERVER;
	playerstatus.PositionZ = protoPlayerStatus.positionz();
	playerstatus.Pitch = protoPlayerStatus.pitch();
	playerstatus.Yaw = protoPlayerStatus.yaw();
	playerstatus.Roll = protoPlayerStatus.roll();
	playerstatus.SpeedX = protoPlayerStatus.speedx();
	playerstatus.SpeedY = protoPlayerStatus.speedy();
	playerstatus.SpeedZ = protoPlayerStatus.speedz();
	playerstatus.IsAlive = protoPlayerStatus.isalive();
	playerstatus.HealthValue = protoPlayerStatus.healthvalue();
	playerstatus.IsAttacking = protoPlayerStatus.isattacking();
}

void ClientSocket::FromMonsterStatusToProtoStatus(stMonsterStatus& monsterstatus, const SceneMsg::Struct_Monster_Status& protoMonsterStatus)
{
	monsterstatus.uuid = protoMonsterStatus.roleuid();
	monsterstatus.PositionX = protoMonsterStatus.positionx() * UE4_LOCATION_TO_SERVER;
	monsterstatus.PositionY = protoMonsterStatus.positiony() * UE4_LOCATION_TO_SERVER;
	monsterstatus.PositionZ = protoMonsterStatus.positionz();
	monsterstatus.IsAlive = protoMonsterStatus.isalive();
	monsterstatus.HealthValue = protoMonsterStatus.healthvalue();
	monsterstatus.IsAttacking = protoMonsterStatus.isattacking();
}

void ClientSocket::NewPlayerEnterScene(char* data, int len)
{
	SceneMsg::Scene_Brocast_new_player_enter_22006 NewPlayerBrocast;
	if (!NewPlayerBrocast.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("测试登录  请求  parse failed! "));
		return;
	}

	SceneMsg::Struct_Player_Status recvPlayerStatus = NewPlayerBrocast.newplayerstatus();
	stPlayerStatus newPlayerStatus;
	FromPlayerStatusToProtoStatus(newPlayerStatus, recvPlayerStatus);
	PlayerController->OtherPlayerEnterInsight(newPlayerStatus);
	
}

void ClientSocket::MovementStatusChanged(APlayerCharacter* CurPlayer, const FVector& new_location)
{
	if (!CurPlayer)
	{
		return;
	}

	SceneMsg::Scene_Player_Movement_Request_22002 CurPlayerStatus;
	SceneMsg::Struct_Player_Status* CurSelfStatus = new SceneMsg::Struct_Player_Status;
	FromPlayerCharacterToProtoStatus(CurPlayer, CurSelfStatus);

	if (new_location.X <= 0)
	{
		CurSelfStatus->set_positionx(FMath::FloorToInt(new_location.X / UE4_LOCATION_TO_SERVER));
	}
	else
	{
		CurSelfStatus->set_positionx(FMath::CeilToInt(new_location.X / UE4_LOCATION_TO_SERVER));
	}

	if (new_location.Y <= 0)
	{
		CurSelfStatus->set_positiony(FMath::FloorToInt(new_location.Y / UE4_LOCATION_TO_SERVER));
	}
	else
	{
		CurSelfStatus->set_positiony(FMath::CeilToInt(new_location.Y / UE4_LOCATION_TO_SERVER));
	}

	if (new_location.Z <= 0)
	{
		CurSelfStatus->set_positionz(FMath::FloorToInt(new_location.Z));
	}
	else
	{
		CurSelfStatus->set_positionz(FMath::CeilToInt(new_location.Z));
	}

	//CurPlayerStatus.set_sessionid(CurPlayer->SessionID);
	CurPlayerStatus.set_allocated_selfstatus(CurSelfStatus);

	const auto& Location = CurPlayer->GetActorLocation();
	const auto& Velocity = CurPlayer->GetVelocity();

	//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, *Rotation.ToString(), *Location.ToString());
	if (!SendDataToServer(EPacketTypeScene::PLAYER_MOVEMENT_REQ, CurPlayerStatus))
		return;

}

void ClientSocket::PlayerMovementRsp(char* data, int len)
{
	if (!PlayerController)
	{
		return;
	}

	SceneMsg::Scene_Player_Movement_Response_22003 SyncOtherPlayers;
	if (!SyncOtherPlayers.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("请求移动状态改变失败! "));
		return;
	}

	int32_t errorCode = SyncOtherPlayers.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("请求移动失败! "));
		return;
	}

	// 移动成功
}


void ClientSocket::OtherPlayerMovementBrocast(char* data, int len)
{
	if (!PlayerController)
	{
		return;
	}

	SceneMsg::Scene_Brocast_player_Movement_22011 BrocastOtherPlayerMovement;
	if (!BrocastOtherPlayerMovement.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("recv other player status failed! "));
		return;
	}

	int32_t errorCode = BrocastOtherPlayerMovement.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("brocast other player status failed! "));
		return;
	}


	SceneMsg::Struct_Player_Status otherPlayerStatus = BrocastOtherPlayerMovement.playernewstatus();
	stPlayerStatus newPlayerStatus;
	FromPlayerStatusToProtoStatus(newPlayerStatus, otherPlayerStatus);
	PlayerController->UpdateOtherPlayerStatus(newPlayerStatus);

}

void ClientSocket::OtherPlayerHitMonster(char* data, int len)
{
	if (!PlayerController)
	{
		return;
	}

	SceneMsg::Scene_Brocast_Player_Attack_Monster_22010 OtherPlayerHitMonster;
	if (!OtherPlayerHitMonster.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("parse other player move msg failed! "));
		return;
	}

	int32_t errorCode = OtherPlayerHitMonster.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("other player attack monster failed! "));
		return;
	}

	int64_t attackerUUID = OtherPlayerHitMonster.attackeruuid();
	int64_t monsterUUID = OtherPlayerHitMonster.hurteduuid();

	PlayerController->OtherPlayerHitMonster(attackerUUID, monsterUUID);

}

void ClientSocket::HitMonster(APlayerCharacter* CurPlayer)
{
	if (!CurPlayer)
	{
		return;
	}

	SceneMsg::Player_Hit_Monster_Request_22008 PlayerHitMonster;
	PlayerHitMonster.set_sessionid(CurPlayer->SessionID);
	PlayerHitMonster.set_monsteruuid(10000);

	if (!SendDataToServer(EPacketTypeScene::PLAYER_HIT_MONSTER_REQ, PlayerHitMonster))
		return;

}

void ClientSocket::OtherEntityPropChanged(char* data, int len)
{
	if (!PlayerController)
	{
		return;
	}

	EntityMsg::Brocast_Other_Prop_Change_23001 EntityPropChange;
	if (!EntityPropChange.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("parse Other Entity Prop change msg failed! "));
		return;
	}

	int32_t errorCode = EntityPropChange.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("brocast other entity prop changed! "));
		return;
	}

	int64_t entityID = EntityPropChange.entityuuid();

	EntityMsg::Struct_Property changedProp;
	int changePropSize = EntityPropChange.changedprops_size();
	for (int i = 0; i < changePropSize; ++i)
	{
		changedProp = EntityPropChange.changedprops(i);
		PlayerController->OnEntityPropChanged(entityID, changedProp.propid(), changedProp.value());
	}
}

void ClientSocket::SyncOtherEntitiesProps(char* data, int len)
{
	if (!PlayerController)
	{
		return;
	}

	EntityMsg::Brocast_All_Eitities_Prop_23002 AllEntitiesProps;
	if (!AllEntitiesProps.ParseFromArray(data, len))
	{
		UE_LOG(LogTemp, Log, TEXT("parse All Entities Props msg failed! "));
		return;
	}

	int32_t errorCode = AllEntitiesProps.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("brocast all Entities Props failed! "));
		return;
	}

	int entityPropSize = AllEntitiesProps.entitiesprops_size();
	for (int i = 0; i < entityPropSize; ++i)
	{
		// 解析实体属性
		std::unordered_map<int32_t, int32_t> allProps;
		EntityMsg::Struct_Entity_Properties OnePair = AllEntitiesProps.entitiesprops(i);
		int64_t entityUUID = OnePair.entityuuid();
		int propSize = OnePair.properties_size();
		for (int j = 0; j < propSize; ++j)
		{
			EntityMsg::Struct_Property property = OnePair.properties(j);
			allProps.insert(std::make_pair(property.propid(), property.value()));
		}

		PlayerController->OnEntityPropInitialize(entityUUID, allProps);
	}
}



void ClientSocket::NotifyPlayerWhenEntityEnter(char* data, int len)
{
	SceneMsg::Scene_Notify_Self_Other_Entity_Enter other_entity_status;
	if (!other_entity_status.ParseFromArray(data, len))
		return;

	int32_t errorCode = other_entity_status.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("enter scene failed !  errorCode : %d "), errorCode);
		return;
	}

	SceneMsg::Struct_Player_Status otherPlayerStatus;
	int otherPlayerSize = other_entity_status.playersstatus_size();
	for (int i = 0; i < otherPlayerSize; ++i)
	{
		otherPlayerStatus = other_entity_status.playersstatus(i);
		stPlayerStatus newPlayerStatus;
		FromPlayerStatusToProtoStatus(newPlayerStatus, otherPlayerStatus);
		PlayerController->OtherPlayerEnterInsight(newPlayerStatus);
	}

	SceneMsg::Struct_Monster_Status monsterStatus;
	int monsterSize = other_entity_status.monsterstatus_size();
	for (int i = 0; i < monsterSize; ++i)
	{
		monsterStatus = other_entity_status.monsterstatus(i);
		stMonsterStatus newMonsterStatus;
		FromMonsterStatusToProtoStatus(newMonsterStatus, monsterStatus);
		PlayerController->UpdateOtherMonster(newMonsterStatus);
	}

}

void ClientSocket::NotifyPlayerWhenEntityLeave(char* data, int len)
{

	SceneMsg::Scene_Notify_Self_Other_Entity_Leave other_entity_leave;
	if (!other_entity_leave.ParseFromArray(data, len))
		return;

	int32_t errorCode = other_entity_leave.error();
	if (errorCode != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("leave scene failed !  errorCode : %d "), errorCode);
		return;
	}

	if (!PlayerController)
	{
		return;
	}

	int leave_entity_size = other_entity_leave.leaveduuid_size();
	// 先用低效的方式遍历删除 entity
	for (int i = 0; i < leave_entity_size; i++)
	{
		PlayerController->RemovePlayerEntity(other_entity_leave.leaveduuid(i));
	}

}

bool ClientSocket::Init()
{
	return InitSocket();
}

uint32 ClientSocket::DealWithServerMsg()
{
	uint32 pendingSize = 0;
	if (!SocketClient->HasPendingData(pendingSize))
	{
		return -1;
	}

	char	recvData[MAX_BUFFER];
	int32_t read = 0;
	SocketClient->Recv((uint8*)recvData, MAX_BUFFER, read);
	if (read > 0)
	{
		DistributeMsg(recvData, read);
	}

	return 0;
}

void ClientSocket::DistributeMsg(char* recvData, int32_t dataLen)
{
	uint16_t msgID = 0;
	FMemory::Memcpy(&msgID, recvData, sizeof(msgID));
	uint16_t dataSize = 0;
	FMemory::Memcpy(&dataSize, recvData + sizeof(msgID), sizeof(dataSize));
	if (dataSize == dataLen)
	{
		switch (msgID)
		{
		case BROCAST_NEW_PLAYER:
			NewPlayerEnterScene(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case ENROLL_ENTER_SCENE_RPO:
			EnterSceneRsp(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case PLAYER_MOVEMENT_RPO:
			PlayerMovementRsp(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case BROCAST_PLAYER_MOVEMENT:
			OtherPlayerMovementBrocast(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case BROCAST_PLAYER_HIT_MONSTER:
			OtherPlayerHitMonster(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case BROCAST_OTHER_PROP_CHANGE:
			OtherEntityPropChanged(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;
		case BROCAST_ALL_ENTITIES_PROPS:
			SyncOtherEntitiesProps(recvData + sizeof(msgID) + sizeof(dataSize), dataLen - sizeof(msgID) - sizeof(dataSize));
			break;

		default:
			break;
		}
	}
	else
	{
		int32_t startPos = 0;
		while (dataSize + startPos <= dataLen)
		{
			switch (msgID)
			{
			case BROCAST_NEW_PLAYER:
				NewPlayerEnterScene(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case ENROLL_ENTER_SCENE_RPO:
				EnterSceneRsp(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case PLAYER_MOVEMENT_RPO:
				PlayerMovementRsp(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case BROCAST_PLAYER_MOVEMENT:
				OtherPlayerMovementBrocast(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case BROCAST_PLAYER_HIT_MONSTER:
				OtherPlayerHitMonster(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case BROCAST_OTHER_PROP_CHANGE:
				OtherEntityPropChanged(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;
			case BROCAST_ALL_ENTITIES_PROPS:
				SyncOtherEntitiesProps(recvData + startPos + sizeof(msgID) + sizeof(dataSize), dataSize - sizeof(msgID) - sizeof(dataSize));
				break;


			default:
				return;
				break;
			}

			startPos = startPos + dataSize;
			FMemory::Memcpy(&msgID, recvData + startPos, sizeof(msgID));
			FMemory::Memcpy(&dataSize, recvData + startPos + sizeof(msgID), sizeof(dataSize));

		}
	}


}
