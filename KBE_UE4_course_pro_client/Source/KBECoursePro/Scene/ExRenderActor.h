// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExRenderActor.generated.h"

// 用来在场景里渲染RenderTexture 给界面使用
UCLASS()
class KBECOURSEPRO_API AExRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExRenderActor();


	UFUNCTION(BlueprintImplementableEvent)
		void SwitchRoleMesh(uint8 RoleType);



};
