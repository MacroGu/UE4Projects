// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPCCourseGameMode.generated.h"

UCLASS(minimalapi)
class ARPCCourseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPCCourseGameMode();

	// 用户进入
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// 用户退出
	virtual void Logout(AController* Exiting) override;

};



