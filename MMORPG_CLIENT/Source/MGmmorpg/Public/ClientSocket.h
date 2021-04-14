// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "GameFramework/GameModeBase.h"
#include <google/protobuf/message.h>
#include "Proto/login.pb.h"
#include "Proto/scene.pb.h"
#include "Proto/entity.pb.h"
#include "LogicalDefinition.h"
#include "Protocol.h"


#define	MAX_BUFFER		4096

class AMGPlayerController;
class APlayerCharacter;

/**
 * 
 */
class MGMMORPG_API ClientSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();

	// 初始化 socket
	bool InitSocket();
	// 连接服务器
	bool ConnectServer();
	// 设置服务器的IP 和port
	void SetServerIPandPort(const FString& serverIP, const int32& serverPort);

	// 注册
	bool SignUp(const FText& Account, const FText& Pw);
	bool SignUpRsp(char* data, int len);
	// 登录
	bool Login(const FText& Account, const FText& Pw);
	bool LoginRsp(char* data, int len);
	// 请求进入场景
	void EnterScene(APlayerCharacter* CurPlayer);
	// 请求进入场景  回复
	void EnterSceneRsp(char* data, int len);
	//收到其他玩家进入场景
	void NewPlayerEnterScene(char* data, int len);	
	// 发送玩家自己的状态   请求发送自身状态的情况多种，但共用此接口
	void MovementStatusChanged(APlayerCharacter* CurPlayer, const FVector& new_location);
	// 玩家请求状态改变 ，服务器返回
	void PlayerMovementRsp(char* data, int len);
	// 接收到服务器广播其他玩家的状态  同步其他玩家的状态
	void OtherPlayerMovementBrocast(char* data, int len);
	// 接收到服务器广播， 玩家攻击怪物
	void OtherPlayerHitMonster(char* data, int len);
	// 攻击其怪物
	void HitMonster(APlayerCharacter* CurPlayer);
	// 怪物属性变化
	void OtherEntityPropChanged(char* data, int len);
	// 同步其他实体属性
	void SyncOtherEntitiesProps(char* data, int len);

	// 由于自己的移动或者进入场景， 需要初始化一些新的实体
	void NotifyPlayerWhenEntityEnter(char* data, int len);
	// 由于自己的移动或者离开场景， 需要销毁一些新的实体
	void NotifyPlayerWhenEntityLeave(char* data, int len);

	// 从 player character to proto status
	void FromPlayerCharacterToProtoStatus(APlayerCharacter* player, SceneMsg::Struct_Player_Status* protostatus);
	// 从 stPlayerStatus 到 proto status
	void FromPlayerStatusToProtoStatus(stPlayerStatus& playerstatus,const SceneMsg::Struct_Player_Status& protoPlayerStatus);
	// 从 stMonsterStatus 到 proto status
	void FromMonsterStatusToProtoStatus(stMonsterStatus& monsterstatus, const SceneMsg::Struct_Monster_Status& protoMonsterStatus);

	// 分发消息
	void DistributeMsg(char* recvData, int32_t dataLen);

	// 设置 playercontroller
	void SetPlayerController(AMGPlayerController* pPlayerController);
	// 设置 login game mode
	void SetCurrentGameMode(AGameModeBase* GameMode);
	// 发送数据 统一接口
	bool SendDataToServer(const uint16_t& msgID, ::google::protobuf::Message& protobufData);
	// is login success
	bool IsLoginSuccess() { return isLoginSuccess; }

	int32_t GetSessionID() { return sessionID; }

	uint32 DealWithServerMsg();
	virtual bool Init();

	static ClientSocket* GetSingleton()
	{
		static ClientSocket ins;
		return &ins;
	}

private:
	FSocket* SocketClient;
	FString serverIP;
	int32 serverPort;
	int32 sessionID;		// 客户端唯一 session ID
	bool isLoginSuccess;

	AMGPlayerController* PlayerController;	// player Controller 玩家
	AGameModeBase* CurrentGameMode;			// 当前的gamemode

};
