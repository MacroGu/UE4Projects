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
}

void USlAiPlayerAnim::UpdateMontage()
{
	// 如果不存在直接返回， 避免空指针产生终端
	if (!SPCharacer) return;
	if (!Montage_IsPlaying(PlayerPunchMontage))
	{
		Montage_Play(PlayerPunchMontage);
	}

}
