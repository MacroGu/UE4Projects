// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "SlAiTypes.h"

#include "SlAiPlayerCharacter.generated.h"



UCLASS()
class SLAICOURSE_API ASlAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 修改视角
	void ChangeView(EGameViewMode::Type NewGameView);

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		class UCameraComponent* ThirdCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		UCameraComponent* FirstCamera;

	// 当前的视角模型
	EGameViewMode::Type GameView;

	// 上半身动画状态
	EUpperBody::Type UpperType;

	// 是否运行切换视角
	bool IsAllowSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAtRate(float Value);
	void Turn(float Value);
	void TurnAtRate(float Value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();

private:
	// 第一人称的骨骼模型
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		USkeletalMeshComponent* MeshFirst;
	
	

	// 旋转的比例
	float BaseLookUpRate;
	float BaseTurnRate;

};
