// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExCharacterEntity.h"
#include "Center/ExMmoGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"


// Sets default values
AExCharacterEntity::AExCharacterEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = 500;
}

// Called when the game starts or when spawned
void AExCharacterEntity::BeginPlay()
{
	Super::BeginPlay();
	
	// 如果不是玩家
	if (!IsPlayer && MmoGameMode)
	{
		MmoGameMode->CharacterMap.Add(EntityId, this);
	}

	// 初始化数据
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

	// 获取动作蓝图
	CharacterAnim = GetMesh()->GetAnimInstance();

	// 刷新一次实体数据到UE4 对象
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst)
	{
		EntityInst->callPropertysSetMethods();
	}

}

void AExCharacterEntity::Destroyed()
{
	Super::Destroyed();

	// 如果不是玩家
	if (!IsPlayer && MmoGameMode)
	{
		MmoGameMode->CharacterMap.Remove(EntityId);
	}
}

void AExCharacterEntity::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	// 获取更新时间间隔
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	// 保存当前时间
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	// 获取距离
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	// 计算出实时速度
	MoveSpeed = Distance / UpdatePositionSpaceTime;

}

void AExCharacterEntity::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}

void AExCharacterEntity::SetTargetAnim(float Speed, float Direction)
{
	// 获取插值头尾状态
	TargetSpeed = Speed;
	TargetDirection = Direction;
	LastSpeed = AnimSpeed;
	LastDirection = AnimDirection;

	// 获取时间间隔
	UpdateAnimSpaceTime = GetWorld()->TimeSeconds - LastUpdateAnimTime;
	RemainAnimSpaceTime = UpdateAnimSpaceTime;
	// 保留上一次更新的时间
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

}

void AExCharacterEntity::OnAttack()
{
	if (CharacterAnim)
	{
		CharacterAnim->Montage_Play(AttackMontage);
	}
}
