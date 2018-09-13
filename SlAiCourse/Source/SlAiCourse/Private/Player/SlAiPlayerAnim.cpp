// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerAnim.h"
#include "SlAiPlayerCharacter.h"



USlAiPlayerAnim::USlAiPlayerAnim()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f,0.f,0.f);
}

void USlAiPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// 初始化角色指针
	InitSPCharacter();
	// 更新蓝图数据
	UpdateParameter();
	// 更新动作
	UpdateMontage();

}

void USlAiPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!SPCharacer) return;

	SPCharacer->ChangeHandObjectDetect(IsOpen);

}

void USlAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacer)
	{
		SPCharacer = Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
	}
}

void USlAiPlayerAnim::UpdateParameter()
{
	// 如果不存在直接返回， 避免空指针产生终端
	if (!SPCharacer) return;
	// 设置速度
	Speed = SPCharacer->GetVelocity().Size();
	// 更新上半身的旋转
	float SpineDir = SPCharacer->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void USlAiPlayerAnim::UpdateMontage()
{
	// 如果不存在直接返回， 避免空指针产生终端
	if (!SPCharacer) return;

	// 如果当前的人称状态和这个动作的不一致，直接返回
	if (SPCharacer->GameView != GameView) return;

	// 如果当前动作没有停止，不更新动作
	if (!Montage_GetIsStopped(CurrentMontage)) return;
	
	switch (SPCharacer->UpperType)
	{
	case EUpperBody::None:
		if (CurrentMontage != nullptr)
		{
			Montage_Stop(0);
			CurrentMontage = nullptr;
			// 允许切换视角
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			// 不允许切换视角
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			AllowViewChange(false);
		}
		break;
	default:
		break;
	}
	
}

void USlAiPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacer) return;
	SPCharacer->IsAllowSwitch = IsAllow;
}
