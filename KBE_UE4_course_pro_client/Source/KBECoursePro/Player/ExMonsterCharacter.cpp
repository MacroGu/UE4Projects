// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExMonsterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "HUD/ExBloodBar.h"
#include "Animation/AnimInstance.h"
#include <Scripts/ExCommon.h>



AExMonsterCharacter::AExMonsterCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	BloodBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BloodBar"));
	BloodBarComponent->SetupAttachment(RootComponent);

}

void AExMonsterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 位置更新
	FVector CurrentPosition = GetActorLocation();

	FVector MoveDirection = TargetPosition - CurrentPosition;

	float DeltaSpace = DeltaSeconds * MoveSpeed;

	float Distance = MoveDirection.Size();

	// 距离太大或者太小就直接设置位置
	if (Distance > 300.f || Distance < DeltaSpace)
	{
		SetActorLocation(TargetPosition);
	}
	else
	{
		// 移动位置
		MoveDirection.Normalize();
		SetActorLocation(CurrentPosition + MoveDirection * DeltaSpace);
	}

	// 旋转更新
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaSeconds, 5.f);
	FaceRotation(CurrentRotation);

	// 更新动作
	RemainAnimSpaceTime -= DeltaSeconds * 5;
	float AnimLerpPercent = FMath::Clamp(RemainAnimSpaceTime / UpdateAnimSpaceTime, 0.f, 1.f);
	AnimSpeed = FMath::Lerp(TargetSpeed, LastSpeed, AnimLerpPercent);
	AnimDirection = FMath::Lerp(TargetDirection, LastDirection, AnimLerpPercent);

	// 设置血条朝向
	FVector CameraPos = UExCommon::Get()->GetCameraPos();
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(CameraPos.X, CameraPos.Y, 0.f);
	BloodBarComponent->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());

}

void AExMonsterCharacter::SetBaseHP(int32 InBaseHP)
{
	BaseHP = InBaseHP;
}

void AExMonsterCharacter::SetHP(int32 InHP)
{
	if (InHP > 0)
	{
		// 播放受伤动画
		CharacterAnim->Montage_Play(HurtMontage);
	}

	HP = InHP;
	float HpPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar)
	{
		BloodBar->SetHpPercent(HpPercent);
	}
}

void AExMonsterCharacter::PlayDeath()
{
	// 动画由状态机自己判定HP 是否小于0来播放

	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AExMonsterCharacter::MonsterDestroy, 5.f);

}

void AExMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 获取血条
	BloodBar = Cast<UExBloodBar>(BloodBarComponent->GetUserWidgetObject());
	BloodBar->SetRole(RoleType, RoleName);
}

void AExMonsterCharacter::MonsterDestroy()
{
	Destroy();
}
