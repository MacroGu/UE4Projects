// Fill out your copyright notice in the Description page of Project Settings.


#include "RPCInstance.h"
#include "../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "../Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h"
#include <GameFramework/PlayerController.h>
#include "ExCommon.h"
#include <UObject/CoreOnline.h>
#include "../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include <Delegates/IDelegateInstance.h>
#include <Kismet/GameplayStatics.h>



URPCInstance::URPCInstance()
{
	// 绑定回调函数
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnStartOnlineGameComplete);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &URPCInstance::OnFindSessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnJoinSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnDestroySessionComplete);

}

void URPCInstance::AssignPlayerController(APlayerController* InController)
{
	PlayerController = InController;

	// 获取OnlineSub
	// 获取方式一：Online::GetSubsystem(GetWorld(), NAME_None); 推荐方式
	// 获取方式二：使用IOnlineSubsystem::Get(), 直接获取可以createSession但是joinSession后客户端没有跳转场景
	OnlineSub = Online::GetSubsystem(PlayerController->GetWorld(), NAME_None);

	// 获取UserID
	// 获取方式一： UGameplayStatics::GetGameInstance(GetWorld())->GetLocalPlayer()[0]->GetPreferredUniqueNetId()
	if (GetLocalPlayers().Num() == 0)
	{
		DDH::Debug() << "No LocalPlayer Exis, Can't Get UserID" << DDH::Endl();
	}
	else
	{
		UserID = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();
	}


#if 0
	// 获取方式二： 使用PlayerState获取, 该方式打包成exe没有问题， 在编辑器模式下多个窗口会找不到 Playerstate
	if (PlayerController->PlayerState)
	{
		UserID = PlayerController->PlayerState->UniqueId.GetUniqueNetId();
	}
#endif

	// 在这里直接获取 Session 运行时会报错，生命周期的问题



}

void URPCInstance::HostSession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 会话设置
			FOnlineSessionSettings Settings;
			// 连接数
			Settings.NumPublicConnections = 10;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;
			// 使用局域网
			Settings.bIsLANMatch = true;
			Settings.bUsesPresence = true;
			Settings.bAllowJoinViaPresence = true;
			// 绑定委托
			OnCreateSessionCompleteDelegateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			// 创建绘画
			Session->CreateSession(*UserID, NAME_GameSession, Settings);

		}
	}
}

void URPCInstance::ClientSession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 实例化搜索结果指针并且设定参数
			SearchObject = MakeShareable(new FOnlineSessionSearch);
			// 返回结果
			SearchObject->MaxSearchResults = 10;
			// 是否是局域网，就是 IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
			// 绑定寻找会话委托
			OnFindSessionsCompleteDelegateHandle = Session->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			// 进行会话寻找
			Session->FindSessions(*UserID, SearchObject.ToSharedRef());

		}

	}
}

void URPCInstance::DestroySession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 绑定销毁会话委托
			OnDestroySessionCompleteDelegateHandle = Session->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			// 执行销毁会话
			Session->DestroySession(NAME_GameSession);
		}
	}

}

void URPCInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 解除绑定绘画完成回调函数
			Session->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			// 判断创建会话是否成功
			if (bWasSuccessful)
			{
				DDH::Debug() << "CreateSession Succeed" << DDH::Endl();

				// 绑定开启会话委托
				OnStartSessionCompleteDelegateHandle = Session->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				Session->StartSession(NAME_GameSession);
			}
			else
			{
				DDH::Debug() << "CreateSession Failed" << DDH::Endl();
			}
		}
	}
}

void URPCInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 注销开启会话委托绑定
			Session->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				DDH::Debug() << "StartSession Succeed" << DDH::Endl();
				// 服务端跳转场景
				UGameplayStatics::OpenLevel(PlayerController->GetWorld(), FName("GameMap"), true, FString("listen"));
			}
			else
			{
				DDH::Debug() << "StartSession Failed" << DDH::Endl();
			}
		}

	}
}

void URPCInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 取消寻找会话委托绑定
			Session->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
			// 如果寻找会话成功
			if (bWasSuccessful)
			{
				//如果收集的结构存在并且大于1
				if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
				{
					DDH::Debug() << "Find Session Succeed" << DDH::Endl();
					// 绑定加入session委托
					OnJoinSessionCompleteDelegateHandle = Session->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
					// 执行加入session
					Session->JoinSession(*UserID, NAME_GameSession, SearchObject->SearchResults[0]);
				}
				else
				{
					DDH::Debug() << "Find Session Succeed But Num == 0" << DDH::Endl();
				}
			}
			else
			{
				DDH::Debug() << "Find Session Failed" << DDH::Endl();
			}

		}

	}
}

void URPCInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 取消加入会话委托绑定
			Session->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			// 如果加入成功
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				// 传送玩家到新地图
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					DDH::Debug() << "Join Sessions Succeed " << DDH::Endl();
					// 客户端切换到服务器的关卡
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}

			}

		}

	}
}

void URPCInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// 取消销毁会话委托
			Session->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			// 其他逻辑。。。。

		}
	}
}
