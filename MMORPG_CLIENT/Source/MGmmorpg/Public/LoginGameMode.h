// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientSocket.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MGMMORPG_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties", Meta = (BlueprintProtect = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Login")
	bool Connect(const FText& ServerIp, const FText& ServerPort);

	UFUNCTION(BlueprintCallable, Category = "Login")
	bool Login(const FText& username, const FText& Pw);

	UFUNCTION(BlueprintCallable, Category = "Login")
	bool SignUp(const FText& username, const FText& Pw);

	// ¹Ø±Õ UMG
	void EnterScene();

private:
	bool bIsConnected;
};
