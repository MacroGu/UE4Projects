// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <unordered_map>
#include "GameFramework/PlayerController.h"
#include "LogicalDefinition.h"
#include "MGPlayerController.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class MGMMORPG_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMGPlayerController();
	~AMGPlayerController();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> WhoToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> MonsterToSpawn;


	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 更新场景中的其他的玩家   其他玩家进入场景的时候 
	void OtherPlayerEnterInsight(stPlayerStatus& newPlayerStatus);
	// 更新其他玩家状态   仅更新一个
	bool UpdateOtherPlayerStatus(const stPlayerStatus& OtherPlayerStatus);
	// 更新场景中的其他的怪物   其他玩家进入场景的时候 
	void UpdateOtherMonster(stMonsterStatus& newMonsterStatus);
	// 更新其他怪物的状态
	bool UpdateWorldMonsterInfo(const std::map<int64_t, stPlayerStatus>& updatedInSightMonsters);
	// 其他玩家攻击怪物
	void OtherPlayerHitMonster(const int64_t& attackerUUID, const int64_t& monsterID);
	// 实体属性发生变化
	void OnEntityPropChanged(const int64_t& entityID, const int32_t& ID, const int32_t& Value);
	// 实体属性初始化
	void OnEntityPropInitialize(const int64_t& entityID, const std::unordered_map<int32_t, int32_t>& allProps);
	// 移除玩家实体
	void RemovePlayerEntity(const int64_t iPlayerUUID);
	

	// 产生新的玩家
	void GenerateNewPlayer();

	// 模拟玩家的移动
	void SimulatePlayerRun();

	APlayerCharacter* second_player;

private:

	std::map<int64_t, stPlayerStatus> InSightPlayers;	// 视野范围内的全部玩家
	std::map<int64_t, stMonsterStatus> InSightMonsters; // 视野范围内的怪物

	int					SessionId;

	bool bIsConnected;	// 是否保持连接


	bool bIsChatNeedUpdate;

	int	nPlayers;

	int nMonsters;

	bool bIsNeedToSpawnMonster;

	bool bIsNeedToDestroyMonster;
};
