// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiThirdSlAiPlayerAnim.h"
#include "SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SlAiHelper.h"
#include "ConstructorHelpers.h"


USlAiThirdSlAiPlayerAnim::USlAiThirdSlAiPlayerAnim()
{
	// 绑定资源到Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
	PlayerHitMontage = PlayerHitMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
	PlayerEatMontage = PlayerEatMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
	PlayerFightMontage = PlayerFightMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
	PlayerPunchMontage = PlayerPunchMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
	PlayerPickUpMontage = PlayerPunchMon.Object;


	// 给方向赋值
	Direction = 0.f;
	// 给是否在空中赋值
	IsInAir = false;
}

void USlAiThirdSlAiPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();

	// 如果不存在直接返回， 避免空指针产生终端
	if (!SPCharacer) return;
	// 获取是否在跳跃
	IsInAir = SPCharacer->GetCharacterMovement()->IsFalling();
	// 速度朝向的Yaw旋转减去Actor朝向其实就是摄像机朝向的Yaw旋转得到相对方向
	float PreDir = SPCharacer->GetVelocity().ToOrientationRotator().Yaw - SPCharacer->GetActorRotation().Yaw;
	
	// 输出一下数据
// 	SlAiHelper::Debug(FString("SPCharacter->Velocity : ") + FString::SanitizeFloat(SPCharacer->GetVelocity().ToOrientationRotator().Yaw), 0.f);
// 	SlAiHelper::Debug(FString("SPCharacer : ") + FString::SanitizeFloat(SPCharacer->GetActorRotation().Yaw), 0.f);
// 	SlAiHelper::Debug(FString("PreDir : ") + FString::SanitizeFloat(PreDir), 0.f);

	if (PreDir > 180.f)	PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;

	Direction = PreDir;


	/*SlAiHelper::Debug(FString("Direction : ") + FString::SanitizeFloat(Direction), 0.f);*/
}
