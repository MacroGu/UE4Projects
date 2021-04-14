// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "ClientSocket.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include <chrono>
#include <GameFramework/Pawn.h>
#include "GameFramework/PlayerState.h"
#include "MGPlayerController.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	IsAttacking = false;
	SessionID = -1;
	uuid = -1;

}

void APlayerCharacter::HitOtherCharacter()
{
	IsAttacking = true;

	FName animName = "AnimSequence'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_A_Slow.PrimaryAttack_A_Slow'";
	UAnimationAsset* runAnim = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *animName.ToString()));
	GetMesh()->PlayAnimation(runAnim, false);

	ClientSocket::GetSingleton()->HitMonster(this);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::GenerateNewPlayer()
{

	AMGPlayerController* player_controller = Cast<AMGPlayerController>(Controller);
	if (player_controller)
	{
		player_controller->GenerateNewPlayer();
	}

}

void APlayerCharacter::SimulatePlayerRun()
{
	AMGPlayerController* player_controller = Cast<AMGPlayerController>(Controller);
	if (player_controller)
	{
		player_controller->SimulatePlayerRun();
	}
}

bool APlayerCharacter::CanMoveByHitKeyBoard()
{
	auto time_now = std::chrono::system_clock::now();
	auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch());


	if (duration_in_ms.count() > last_move_time + 1042)
	{
		// 大于动画播放时间，可以移动, 并更新时间
		last_move_time = duration_in_ms.count();
		return true;
	}
	else
	{
		return false;
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	// PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Hit", IE_Pressed, this, &APlayerCharacter::HitOtherCharacter);

// 	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &APlayerCharacter::MoveForward);
// 	PlayerInputComponent->BindAction("MoveBack", IE_Pressed, this, &APlayerCharacter::MoveBack);
// 	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("GeneNew", IE_Pressed, this, &APlayerCharacter::GenerateNewPlayer);
	PlayerInputComponent->BindAction("SimulateRun", IE_Pressed, this, &APlayerCharacter::SimulatePlayerRun);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

}

void APlayerCharacter::DestroyPlayer()
{
	if (!GetWorld())
	{
		return;
	}
	GetWorld()->DestroyActor(this);
}

void APlayerCharacter::PlayMoveWalkMontage(const bool& need_brocast, const FVector& new_location)
{
	FName animName = "AnimMontage'/Game/Role/Walk_Montage.Walk_Montage'";
	UAnimMontage* runAnim = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, *animName.ToString()));
	PlayAnimMontage(runAnim);

	if (need_brocast)
	{
		ClientSocket::GetSingleton()->MovementStatusChanged(this, new_location);
	}
}
