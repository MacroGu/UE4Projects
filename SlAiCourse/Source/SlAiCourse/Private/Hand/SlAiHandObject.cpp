// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

// 手持物品类
#include "SlAiHandNone.h"
#include "SlAiHandWood.h"
#include "SlAiHandStone.h"
#include "SlAiHandApple.h"
#include "SlAiHandMeat.h"
#include "SlAiHandAxe.h"
#include "SlAiHandHammer.h"
#include "SlAiHandSword.h"

#include "SlAiHelper.h"


// Sets default values
ASlAiHandObject::ASlAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 实例化根组件
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// 创建静态模型
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	// 实例化碰撞组件
	AffectionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectionCollision->SetupAttachment(RootComponent);
	AffectionCollision->SetCollisionProfileName(FName("ToolProfile"));


	// 初始化关闭Overlay 检测
	AffectionCollision->SetGenerateOverlapEvents(true);

	// 绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectionCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectionCollision->OnComponentEndOverlap.Add(OverlayEnd);


}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SlAiHelper::Debug(FString("OnOverlayBegin"), 3.f);
}

void ASlAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SlAiHelper::Debug(FString("OnOverlayEnd"), 3.f);
}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AActor> ASlAiHandObject::SpawnHandObject(int objectID)
{
	switch (objectID)
	{
	case 0:
		return ASlAiHandNone::StaticClass();
	case 1:
		return ASlAiHandWood::StaticClass();
	case 2:
		return ASlAiHandStone::StaticClass();
	case 3:
		return ASlAiHandApple::StaticClass();
	case 4:
		return ASlAiHandMeat::StaticClass();
	case 5:
		return ASlAiHandAxe::StaticClass();
	case 6:
		return ASlAiHandHammer::StaticClass();
	case 7:
		return ASlAiHandSword::StaticClass();
	}

	return ASlAiHandNone::StaticClass();
}

