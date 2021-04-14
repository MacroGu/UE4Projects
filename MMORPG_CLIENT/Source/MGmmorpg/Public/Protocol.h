/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891

	消息协议的ID
*/

#pragma once



// 消息类型定义   登录操作   21000 ~ 21999
enum EPacketTypeLogin
{
	REGISTER_ACCOUNT_REQ = 21000,		// 请求注册
	REGISTER_ACCOUNT_RPO = 21001,		// 注册返回
	LOGIN_SERVER_REQ = 21002,			// 请求登录
	LOGIN_SERVER_RPO = 21003,			// 登录返回
	KEY_LOGIN_SERVER_REQ = 20024,		// 请求通过key登录
	KEY_LOGIN_SERVER_RPO = 20025,		// 通过key登录返回
};

// 消息类型定义   场景状态 22000 ~ 22999
enum EPacketTypeScene
{
	ENROLL_ENTER_SCENE_REQ = 22000,		// 进入场景 请求
	ENROLL_ENTER_SCENE_RPO = 22001,		// 进入场景 返回
	PLAYER_MOVEMENT_REQ = 22002,		// 同步场景玩家状态 请求
	PLAYER_MOVEMENT_RPO = 22003,		// 同步场景玩家状态 返回
	LEAVE_SCENE_REQ = 22004,			// 离开场景 请求
	LEAVE_SCENE_RPO = 22005,			// 离开场景 返回
	BROCAST_NEW_PLAYER = 22006,			// 广播 新玩家进入场景
	BROCAST_PLAYER_LEAVE = 22007,		// 广播 玩家离开场景
	PLAYER_HIT_MONSTER_REQ = 22008,		// 玩家请求攻击怪物 请求
	PLAYER_HIT_MONSTER_RPO = 22009,		// 玩家请求攻击怪物 返回
	BROCAST_PLAYER_HIT_MONSTER = 22010,		// 广播 玩家攻击怪物
	BROCAST_PLAYER_MOVEMENT = 22011,		// 广播 玩家在场景内的移动

};


// 消息类型定义  玩家操作相关消息 23000 ~ 23999
enum EPacketTypeEntity
{
	NOTIFY_SELF_PROP_CHANGE = 23000,			// 通知自己属性变化
	BROCAST_OTHER_PROP_CHANGE = 23001,			// 广播告知其他实体属性变化
	BROCAST_ALL_ENTITIES_PROPS = 23002,			// 广播全部相关实体的属性

};

