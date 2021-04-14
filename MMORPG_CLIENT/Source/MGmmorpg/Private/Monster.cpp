// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAIController.h"
#include "LogicalDefinition.h"
#include <Engine/EngineTypes.h>
#include <WidgetComponent.h>
#include <ProgressBar.h>
#include <GameFramework/Actor.h>
#include "Public/TimerManager.h"



AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IsAttacking = false;
	uuid = 0;

	// 初始化 WidgetComponent
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// 设置Widget class 
	UClass* Widget = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UMG/HP_Bar.HP_Bar_C'"));
	WidgetComponent->SetWidgetClass(Widget);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

}

void AMonster::MoveToLocation(const FVector& dest)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(GetController());
	if (Controller)
	{
		Controller->MoveToLocation(dest);
	}

}
float AMonster::GetHealthPercentage()
{


	return 0;
}

void AMonster::SetHpProgress(float value)
{
	if (!WidgetComponent)
	{
		return;
	}

	UUserWidget* CurrentWidget = WidgetComponent->GetUserWidgetObject();
	if (CurrentWidget)
	{
		HPBarProgress = Cast<UProgressBar>(CurrentWidget->GetWidgetFromName(TEXT("ProgressBar_HP")));
		if (HPBarProgress)
		{
			HPBarProgress->SetPercent(value);
		}
	}
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* CurrentWidget = WidgetComponent->GetUserWidgetObject();

	if (CurrentWidget)
	{
		HPBarProgress = Cast<UProgressBar>(CurrentWidget->GetWidgetFromName(TEXT("ProgressBar_HP")));
		if (HPBarProgress)
		{
			HPBarProgress->SetPercent(100.f);
		}
	}

}

void AMonster::DelayDestroyMonster()
{
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->DestroyActor(this);
}

void AMonster::OnPropChanged(const int32_t& ID, int32_t Value)
{
	auto propIter = mPropMap.find(ID);
	if (propIter == mPropMap.end())
	{
		return;
	}

	int32_t oldValue = propIter->second;
	if (oldValue == 0)
	{
		return;
	}

	// 如果是血量变化， 需要特殊处理
	if (ID == ENTITY_PROP_HP)
	{
		if (Value == 0)		// dead
		{
			FName animName = "AnimSequence'/Game/ParagonRampage/Characters/Heroes/Rampage/Animations/Death_A.Death_A'";
			UAnimationAsset* runAnim = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *animName.ToString()));
			GetMesh()->PlayAnimation(runAnim, false);
			GetWorldTimerManager().SetTimer(DestroyDeadMonsterDelay, this, &AMonster::DelayDestroyMonster, 2, false);
		}

		// 设置血条的长度， 和进行血量扣减， 飘字动画
		float percentHp = Value / 100.f;
		SetHpProgress(percentHp);

	}

	SetProp(ID, Value);
}

void AMonster::SetProp(const int32_t& ID, int32_t Value)
{
	if (ID < ENTITY_PROP_BEGIN || ID > ENTITY_PROP_END)
	{
		return;
	}

	auto propIter = mPropMap.find(ID);
	if (propIter == mPropMap.end())
	{
		mPropMap[ID] = Value;
		return;
	}

	propIter->second = Value;
}

int32_t AMonster::GetProp(const int32_t& ID)
{
	if (ID < ENTITY_PROP_BEGIN || ID > ENTITY_PROP_END)
	{
		return 0;
	}

	auto propIter = mPropMap.find(ID);
	if (propIter == mPropMap.end())
	{
		return 0;
	}

	return propIter->second;
}
