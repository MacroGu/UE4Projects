// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandNone.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"



ASlAiHandNone::ASlAiHandNone()
{
	// 不绑定模型

	// 设置碰撞盒属性
	AffectionCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectionCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ASlAiHandNone::BeginPlay()
{
	Super::BeginPlay();

	// 定义物品序号
	ObjectIndex = 0;
}
