// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExRoomWidget.generated.h"


class AExRoomGameMode;
class UScrollBox;
class UEditableTextBox;
class UExRoomItem;
struct FROOM_INFO;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExRoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	AExRoomGameMode* RoomGameMode;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* RoomListScroll;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* RoomNameTextBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExRoomItem> RoomItemClass;

	UPROPERTY()
		TArray<UExRoomItem*> RoomItemGroup;

public:

	void OnReqRoomList(TArray<FROOM_INFO> RoomList);

	void OnCreateRoom(FROOM_INFO RoomInfo);


	UFUNCTION(BlueprintCallable)
		void RefreshEvent();

	UFUNCTION(BlueprintCallable)
		void CreateRoomEvent();

	UFUNCTION(BlueprintCallable)
		void EnterGameEvent();

protected:

	void RoomItemSelect(uint64 RoomId);

};
