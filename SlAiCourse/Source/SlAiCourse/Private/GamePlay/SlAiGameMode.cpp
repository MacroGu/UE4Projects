// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameMode.h"
#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiPlayerState.h"
#include "SlAiGameHUD.h"


#include "SlAiDataHandle.h"
#include "SlAiHelper.h"
#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASlAiGameMode::ASlAiGameMode()
{
	// 允许开启tick 函数
	PrimaryActorTick.bCanEverTick = true;

	// 添加组件
	HUDClass = ASlAiGameHUD::StaticClass();
	PlayerControllerClass = ASlAiPlayerController::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();

}

void ASlAiGameMode::Tick(float DeltaSeconds)
{

}

void ASlAiGameMode::BeginPlay()
{
	SlAiHelper::Debug(FString("DataHandle : ") +SlAiDataHandle::Get()->RecordName, 30.f);
	SlAiHelper::Debug(FString("DataHandle : ") + Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName, 30.f);
}
