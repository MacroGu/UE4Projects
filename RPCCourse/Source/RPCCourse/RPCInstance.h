// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Delegates/IDelegateInstance.h"
#include "RPCInstance.generated.h"


class IOnlineSubsystem;
class APlayerController;

/**
 * 
 */
UCLASS()
class RPCCOURSE_API URPCInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	URPCInstance();

	void AssignPlayerController(APlayerController* InController);

	void HostSession();

	void ClientSession();

	void DestroySession();

protected:

	// 开启服务器回调函数
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	// 加入服务器回调函数
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// 销毁会话回调函数
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

protected:

	APlayerController* PlayerController;

	// 开启服务器委托与句柄
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	// 加入服务器委托与句柄
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	// 销毁会话委托与句柄
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;


	IOnlineSubsystem* OnlineSub;

	TSharedPtr<const FUniqueNetId> UserID;

	// 保存寻找到的Sessions
	TSharedPtr<FOnlineSessionSearch> SearchObject;

};
