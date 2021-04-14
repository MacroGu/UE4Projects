// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExCharacterEntity.generated.h"

class AExMmoGameMode;
class UAnimInstance;
class UAnimMontage;

UCLASS()
class KBECOURSEPRO_API AExCharacterEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExCharacterEntity();

	virtual void Destroyed() override;

	void SetTargetPosition(FVector InPos);

	void SetTargetRotator(FRotator InRot);

	// 设置目标动作的函数
	void SetTargetAnim(float Speed, float Direction);

	virtual void SetBaseHP(int32 InBaseHP) {}

	virtual void SetHP(int32 InHP) {}

	void OnAttack();

public:

	int32 EntityId;

	uint8 RoleType;

	FString RoleName;

	AExMmoGameMode* MmoGameMode;

	bool IsPlayer;

	UPROPERTY(BlueprintReadOnly)
		float AnimSpeed;

	UPROPERTY(BlueprintReadOnly)
		float AnimDirection;

	UPROPERTY(BlueprintReadOnly)
		bool AnimIsInAir;

	UPROPERTY(BlueprintReadOnly)
		int32 HP;

	int32 BaseHP;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
		UAnimMontage* HurtMontage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	// 目标位置
	FVector TargetPosition;

	// 目标选择
	FRotator TargetRotator;

	// 上一次更新位置的时间
	float LastUpdatePositionTime;

	float MoveSpeed;

	// 上一次同步动作的时间
	float LastUpdateAnimTime;

	// 更新动作时间间隔
	float UpdateAnimSpaceTime;

	// 剩余动作更新时间
	float RemainAnimSpaceTime;

	// 目标速度和移动角度
	float TargetSpeed;

	float TargetDirection;

	// 上一次的速度与移动角度
	float LastSpeed;

	float LastDirection;

	// 保存动作蓝图
	UAnimInstance* CharacterAnim;

};
