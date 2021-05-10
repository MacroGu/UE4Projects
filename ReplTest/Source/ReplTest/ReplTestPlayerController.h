// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ReplTestPlayerController.generated.h"

class AReplTestCharacter;
class UMyUserWidget;

UCLASS()
class AReplTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AReplTestPlayerController();

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	//移动角色(只在服务端执行的函数)
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMoveToDest(APawn* Pawn_, const FVector DestLocation);
	bool ServerMoveToDest_Validate(APawn* Pawn_, const FVector DestLocation);
	void ServerMoveToDest_Implementation(APawn* Pawn_, const FVector DestLocation);

	//只在客户端执行的函数（函数体为空，只是测试用）
	UFUNCTION(Client, Reliable)
		void ClientTestFun(FVector Loc, FRotator Rot);
	void ClientTestFun_Implementation(FVector Loc, FRotator Rot);

	void SetSimulatedCharacter(AReplTestCharacter* Char);

	UMyUserWidget* GetLoginWidget();

	void SetPlayerAlias(const FString& PlayerAlias);

	FString PlayerAlias();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:

	//本地的可操控角色
	AReplTestCharacter* SimulatedCharacter;

	UMyUserWidget* LoginWidget;

	FVector LastDestLoc;

	UPROPERTY(Replicated)
	FString PlayerAlias_;
};


