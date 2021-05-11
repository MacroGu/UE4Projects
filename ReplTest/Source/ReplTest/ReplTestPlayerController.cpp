// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ReplTestPlayerController.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"
#include "ReplTestCharacter.h"
#include "MyAIController.h"
#include "ReplTestGameMode.h"
#include "MyUserWidget.h"

AReplTestPlayerController::AReplTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	SimulatedCharacter = NULL;
}

void AReplTestPlayerController::BeginPlay()
{
	//因为客户端启动时的NetMode为NM_Standalone，只有当登陆成功后才会变为NM_Client，所以这里打开UI的条件为NM_Standalone。
	if (GetNetMode() == NM_Standalone)
	{
		if (UClass* BPClass = LoadClass<UMyUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/TopDownCPP/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C'")))
		{
			LoginWidget = CreateWidget<UMyUserWidget>(this, BPClass);
			if (LoginWidget)
			{
				LoginWidget->AddToViewport();
			}
		}
	}
}

void AReplTestPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReplTestPlayerController, PlayerAlias_);
}

bool AReplTestPlayerController::ServerMoveToDest_Validate(APawn* InPawn, const FVector DestLocation)
{
	//判断请求是否非法，不允许当前客户端操控其他客户端的角色
	bool Rs = false;
	if (AReplTestCharacter* RTC = Cast<AReplTestCharacter>(InPawn))
	{
		Rs = RTC->Alias() == PlayerAlias();
	}
	return Rs;
}

void AReplTestPlayerController::ServerMoveToDest_Implementation(APawn* InPawn, const FVector DestLocation)
{
	if (AMyAIController* AIC = Cast<AMyAIController>(InPawn->GetController()))
	{
		AIC->MoveToLocation(DestLocation);
	}
}

void AReplTestPlayerController::ClientTestFun_Implementation(FVector Loc, FRotator Rot)
{
	UE_LOG(LogTemp, Warning, TEXT("aaaaaaaaaaa"));
}

void AReplTestPlayerController::SetSimulatedCharacter(AReplTestCharacter* Char)
{
	SimulatedCharacter = Char;
}

UMyUserWidget* AReplTestPlayerController::GetLoginWidget()
{
	return LoginWidget;
}

void AReplTestPlayerController::SetPlayerAlias(const FString& PlayerAlias)
{
	PlayerAlias_ = PlayerAlias;
}

FString AReplTestPlayerController::PlayerAlias()
{
	return PlayerAlias_;
}

void AReplTestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AReplTestPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AReplTestPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AReplTestPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AReplTestPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AReplTestPlayerController::MoveToTouchLocation);
}

void AReplTestPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (FVector::Dist(LastDestLoc, Hit.ImpactPoint) > 120)
		{
			LastDestLoc = Hit.ImpactPoint;
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AReplTestPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AReplTestPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (SimulatedCharacter)
	{
		//UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		//float const Distance = FVector::Dist(DestLocation, SimulatedCharacter->GetActorLocation());

		//// We need to issue move command only if far enough in order for walk animation to play correctly
		//if (NavSys && (Distance > 120.0f))
		//{
		//	//NavSys->SimpleMoveToLocation(this, DestLocation);
		//	ServerMoveToDest(SimulatedCharacter, DestLocation);
		//}

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString("+++++++++++"));
		ServerMoveToDest(SimulatedCharacter, DestLocation);
	}
}

void AReplTestPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AReplTestPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
