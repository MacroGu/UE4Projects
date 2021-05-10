// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ReplTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Net/UnrealNetwork.h"
#include "MyAIController.h"
#include "ReplTestPlayerController.h"
#include "MyUserWidget.h"

AReplTestCharacter::AReplTestCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteScale(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AutoPossessPlayer = EAutoReceiveInput::Type::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;
	AIControllerClass = AMyAIController::StaticClass();
}

void AReplTestCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void AReplTestCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReplTestCharacter, Alias_);
}

void AReplTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ROLE_SimulatedProxy == GetLocalRole() && NM_Client == GetNetMode())
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			if (AReplTestPlayerController* RTPC = Cast<AReplTestPlayerController>(PC))
			{
				//因为一个客户端首次加载时会有多个玩家的角色进入场景，这里判断哪个角色才是当前客户端的
				if (Alias_ == RTPC->PlayerAlias())
				{
					PC->SetViewTarget(this);
					RTPC->SetSimulatedCharacter(this);
				}
			}
		}
	}
}

void AReplTestCharacter::SetAlias(const FString& Alias)
{
	Alias_ = Alias;
}

FString AReplTestCharacter::Alias()
{
	return Alias_;
}