// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/ExKbeGameMode.h"
#include "ExRoleGameMode.generated.h"

class UExRoleWidget;
class AExRenderActor;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExRoleGameMode : public AExKbeGameMode
{
	GENERATED_BODY()
	

public:
	virtual void InstallEvent() override;


public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UExRoleWidget> RoleWidgetClass;

	UExRoleWidget* RoleWidget;

	AExRenderActor* RenderActor;


protected:

	virtual void BeginPlay() override;

	void OnReqRoleList(const UKBEventData* EventData);

	void OnCreateRole(const UKBEventData* EventData);

	void OnRemoveRole(const UKBEventData* EventData);

	void OnSelectRoleGame(const UKBEventData* EventData);


};
