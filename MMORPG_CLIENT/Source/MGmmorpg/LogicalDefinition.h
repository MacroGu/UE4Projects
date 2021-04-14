/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891

	游戏逻辑需要用的一些定义
*/

#pragma once
#include <stdint.h>


#define UE4_LOCATION_TO_SERVER 100


// 玩家需要同步的状态   
struct stPlayerStatus
{
	// 会话ID， 唯一ID
	int64_t		SessionId;
	int64_t		uid;	//角色唯一uid

	// 位置
	float	PositionX;
	float	PositionY;
	float	PositionZ;
	// 旋转值
	float	Pitch;
	float	Yaw;
	float	Roll;
	// 速度
	float SpeedX;
	float SpeedY;
	float SpeedZ;
	// 是否活着
	bool	IsAlive;
	// 血量
	float	HealthValue;
	// 是否在攻击
	bool	IsAttacking;

	stPlayerStatus()
	{
		ClearStatus();
	}

	~stPlayerStatus()
	{

	}

	void ClearStatus()
	{
		SessionId = 0;
		PositionX = 0.f;
		PositionY = 0.f;
		PositionZ = 0.f;
		Yaw = 0.f;
		Pitch = 0.f;
		Roll = 0.f;
		SpeedX = 0.f;
		SpeedY = 0.f;
		SpeedZ = 0.f;
		IsAlive = false;
		HealthValue = 0.f;
		IsAttacking = false;
	}

	stPlayerStatus& operator = (const stPlayerStatus& newStatus)
	{
		if (this != &newStatus)
		{
			SessionId = newStatus.SessionId;
			PositionX = newStatus.PositionX;
			PositionY = newStatus.PositionY;
			PositionZ = newStatus.PositionZ;
			Yaw = newStatus.Yaw;
			Pitch = newStatus.Pitch;
			Roll = newStatus.Roll;
			SpeedX = newStatus.SpeedX;
			SpeedY = newStatus.SpeedY;
			SpeedZ = newStatus.SpeedZ;
			IsAlive = newStatus.IsAlive;
			HealthValue = newStatus.HealthValue;
			IsAttacking = newStatus.IsAttacking;
		}

		return *this;
	}

};


// 怪物的状态
struct stMonsterStatus
{
	// uuid， 唯一ID
	int64_t		uuid;

	// 位置
	float	PositionX;
	float	PositionY;
	float	PositionZ;

	// 是否活着
	bool	IsAlive;
	// 血量
	float	HealthValue;
	// 是否在攻击
	bool	IsAttacking;
	// 视野范围
	float	TraceRange;
	// 攻击范围
	float	HitRange;
	// 每次移动单元量
	float	MovePoint;
	// 每次攻击单元量
	float	HitPoint;
	// 是否在追寻玩家
	bool IsTracking;

	stMonsterStatus()
	{
		ClearStatus();
	}

	~stMonsterStatus()
	{

	}

	void ClearStatus()
	{
		uuid = 0;
		PositionX = 0.f;
		PositionY = 0.f;
		PositionZ = 0.f;
		IsAlive = false;
		HealthValue = 0.f;
		IsAttacking = false;
		TraceRange = 0.f;
		HitRange = 0.f;
		MovePoint = 0.f;
		HitPoint = 0.f;
		IsTracking = false;

	}

	stMonsterStatus& operator = (const stMonsterStatus& newStatus)
	{
		if (this != &newStatus)
		{
			uuid = newStatus.uuid;
			PositionX = newStatus.PositionX;
			PositionY = newStatus.PositionY;
			PositionZ = newStatus.PositionZ;
			IsAlive = newStatus.IsAlive;
			HealthValue = newStatus.HealthValue;
			IsAttacking = newStatus.IsAttacking;
			TraceRange = newStatus.TraceRange;
			HitRange = newStatus.HitRange;
			MovePoint = newStatus.MovePoint;
			HitPoint = newStatus.HitPoint;
			IsTracking = newStatus.IsTracking;
		}

		return *this;
	}

};

// 场景中 entity 的类型
enum EntityType
{
	ENTITY_TYPE_INVALID = 0,
	ENTITY_TYPE_PLAYER = 1,		//人物
	ENTITY_TYPE_MONSTER = 2,	//怪物

};


// 实体的属性
enum EntityProp
{
	ENTITY_PROP_BEGIN = 0,	// 开始
	ENTITY_PROP_HP = 3,		//当前血量值
	ENTITY_ATTACK_VALUE = 4,		// 攻击力


	ENTITY_PROP_END = 9999,
};
