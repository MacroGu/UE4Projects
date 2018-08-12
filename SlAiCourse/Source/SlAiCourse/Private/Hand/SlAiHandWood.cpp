// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandWood.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"



ASlAiHandWood::ASlAiHandWood()
{
	// 给模型组件添加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeLog_01.SM_Env_TreeLog_01'"));
	// 绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-8.f, -3.f, 7.f));
	BaseMesh->SetRelativeRotation(FRotator(0.1f, 0.1f, 0.1f));
	BaseMesh->SetRelativeScale3D(FVector(0.f, -20.f, 0.f));

	// 设置碰撞盒属性
	AffectionCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectionCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));

}

void ASlAiHandWood::BeginPlay()
{
	Super::BeginPlay();

	// 定义物品序号
	ObjectIndex = 1;
}
