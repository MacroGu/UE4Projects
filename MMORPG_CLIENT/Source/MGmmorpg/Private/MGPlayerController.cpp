// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MGPlayerController.h"
#include "Public/ClientSocket.h"
#include "Public/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/World.h>
#include <string>
#include "Public/TimerManager.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster.h"
#include <Camera/CameraComponent.h>


AMGPlayerController::AMGPlayerController()
{
	//if (ClientSocket::GetSingleton()->IsLoginSuccess())
	{
		ClientSocket::GetSingleton()->SetPlayerController(this);
	}

	InSightPlayers.clear();
	bIsChatNeedUpdate = false;
	bIsNeedToSpawnMonster = false;
	bIsNeedToDestroyMonster = false;
	bIsConnected = false;

	nMonsters = -1;
	nPlayers = -1;
	second_player = nullptr;
	PrimaryActorTick.bCanEverTick = true;
}

AMGPlayerController::~AMGPlayerController()
{

}

void AMGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 处理网络消息
	ClientSocket::GetSingleton()->DealWithServerMsg();

	// 更新场景中人物等状态


}

void AMGPlayerController::BeginPlay()
{

	InSightPlayers.clear();
	SessionId = ClientSocket::GetSingleton()->GetSessionID();

	
	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player)
		return;
	Player->SessionID = SessionId;
	Player->IsAttacking = false;
	ClientSocket::GetSingleton()->EnterScene(Player);

}

void AMGPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

bool AMGPlayerController::UpdateOtherPlayerStatus(const stPlayerStatus& OtherPlayerStatus)
{
	TArray<AActor*> ClientInSightPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), ClientInSightPlayers);

	for (auto OtherPlayerIter : ClientInSightPlayers)
	{
		APlayerCharacter* OtherPlayer = Cast<APlayerCharacter>(OtherPlayerIter);

		if (OtherPlayer && (OtherPlayer->SessionID == OtherPlayerStatus.SessionId) && (OtherPlayer->SessionID != SessionId))
		{
			FVector CharacterLocation(OtherPlayerStatus.PositionX, OtherPlayerStatus.PositionY, OtherPlayerStatus.PositionZ);
			FRotator CharacterRotation(OtherPlayerStatus.Pitch, OtherPlayerStatus.Yaw, OtherPlayerStatus.Roll);
			FVector CharacterVelocity(OtherPlayerStatus.SpeedX, OtherPlayerStatus.SpeedY, OtherPlayerStatus.SpeedZ);
			OtherPlayer->AddMovementInput(CharacterVelocity);
			OtherPlayer->SetActorRotation(CharacterRotation);
			OtherPlayer->SetActorLocation(CharacterLocation);
			UE_LOG(LogTemp, Log, TEXT("pitch %f, yaw: %f, roll: %f"), OtherPlayerStatus.Pitch, OtherPlayerStatus.Yaw,
				OtherPlayerStatus.Roll);

			break;
		}
	}

	return true;
}

void AMGPlayerController::UpdateOtherMonster(stMonsterStatus& newMonsterStatus)
{
	UWorld* const world = GetWorld();

	if (!world)
	{
		return;
	}

	// 如果已经在视野范围内， 则不能再次进入
	if (InSightMonsters.find(newMonsterStatus.uuid) != InSightMonsters.end())
	{
		return;
	}

	FVector SpawnLocation;
	SpawnLocation.X = newMonsterStatus.PositionX;
	SpawnLocation.Y = newMonsterStatus.PositionY;
	SpawnLocation.Z = newMonsterStatus.PositionZ;

	FRotator SpawnRotation;
	SpawnRotation.Yaw = 0;
	SpawnRotation.Pitch = 0;
	SpawnRotation.Roll = 0;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator<AMonster>();
	SpawnParams.Name = FName(*FString(std::to_string(newMonsterStatus.uuid).c_str()));

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forces the pawn to spawn even if colliding
	AMonster* SpawnCharacter = world->SpawnActor<AMonster>(MonsterToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	SpawnCharacter->SpawnDefaultController();
	SpawnCharacter->IsAttacking = false;
	SpawnCharacter->uuid = newMonsterStatus.uuid;


	// 添加该玩家到视野范围内
	InSightMonsters.insert(std::make_pair(newMonsterStatus.uuid, newMonsterStatus));
}

bool AMGPlayerController::UpdateWorldMonsterInfo(const std::map<int64_t, stPlayerStatus>& updatedInSightMonsters)
{

	return true;
}

void AMGPlayerController::OtherPlayerHitMonster(const int64_t& attackerUUID, const int64_t& monsterID)
{

	if (InSightPlayers.find(attackerUUID) == InSightPlayers.end())
	{
		// 不在视野范围内的攻击  不关心
		return;
	}

	TArray<AActor*> ClientInSightPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), ClientInSightPlayers);

	APlayerCharacter* attacker = nullptr;
	AMonster* monster = nullptr;
	for (auto OtherPlayerIter : ClientInSightPlayers)
	{
		APlayerCharacter* OtherPlayer = Cast<APlayerCharacter>(OtherPlayerIter);
		if (OtherPlayer)
		{
			if (OtherPlayer->SessionID == -1 || OtherPlayer->SessionID == SessionId)
			{
				continue;
			}

			if (OtherPlayer->uuid == attackerUUID)
			{
				// 找到了攻击者
				attacker = OtherPlayer;
			}
		}

		AMonster* hurted = Cast<AMonster>(OtherPlayerIter);
		if (hurted)
		{
			if (hurted->uuid == monsterID)
			{
				monster = hurted;
			}
		}
	}

	// 找到了攻击者与被攻击者， 开始播放动画 等
	if (!attacker)
	{
		return;
	}
	
	auto sm = attacker->GetMesh();
	if (sm)
	{
		FName animName = "AnimSequence'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_A_Slow.PrimaryAttack_A_Slow'";
		UAnimationAsset* runAnim = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *animName.ToString()));

		sm->PlayAnimation(runAnim, false);
	}

}

void AMGPlayerController::OnEntityPropChanged(const int64_t& entityID, const int32_t& ID, const int32_t& Value)
{
	UWorld* const world = GetWorld();
	if (!world)
	{
		return;
	}

	// 暂时先只考虑 怪物的属性变化
	if (InSightMonsters.find(entityID) == InSightMonsters.end())
	{
		return;
	}

	TArray<AActor*> ClientInSightMonster;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), ClientInSightMonster);
	for (auto OneMonsterIter : ClientInSightMonster)
	{
		AMonster* otherMonster = Cast<AMonster>(OneMonsterIter);

		if (otherMonster && otherMonster->uuid == entityID)
		{
			otherMonster->OnPropChanged(ID, Value);
			break;
		}
	}
}

void AMGPlayerController::OnEntityPropInitialize(const int64_t& entityID, const std::unordered_map<int32_t, int32_t>& allProps)
{
	UWorld* const world = GetWorld();
	if (!world)
	{
		return;
	}

	// 只有视野范围内的entity 才考虑更新
	if (InSightMonsters.find(entityID) == InSightMonsters.end() && 
		InSightPlayers.find(entityID) == InSightPlayers.end())
	{
		return;
	}

	if (allProps.empty())
	{
		return;
	}

	TArray<AActor*> ClientInSightMonster;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), ClientInSightMonster);
	for (auto OneMonsterIter : ClientInSightMonster)
	{
		AMonster* otherMonster = Cast<AMonster>(OneMonsterIter);
		if (otherMonster && otherMonster->uuid == entityID)
		{
			for (auto oneProp : allProps)
			{
				otherMonster->SetProp(oneProp.first, oneProp.second);
			}

			break;
		}
	}
}

void AMGPlayerController::RemovePlayerEntity(const int64_t iPlayerUUID)
{
	if (!GetWorld())
	{
		return;
	}
	if (!InSightPlayers.count(iPlayerUUID))
	{
		return;
	}

	TArray<AActor*> ClientInSightPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), ClientInSightPlayers);

	APlayerCharacter* _playerCharacter;
	for (auto onePlayer : ClientInSightPlayers)
	{
		_playerCharacter = Cast<APlayerCharacter>(onePlayer);
		if (_playerCharacter)
		{
			if (_playerCharacter->uuid == iPlayerUUID)
			{
				_playerCharacter->DestroyPlayer();
				break;
			}
		}
	}
	InSightPlayers.erase(iPlayerUUID);
}

void AMGPlayerController::GenerateNewPlayer()
{
	if (second_player)
	{
		return;
	}

	FVector SpawnLocation;
	SpawnLocation.X = 200.0;
	SpawnLocation.Y = 100.0;
	SpawnLocation.Z = 30.0;

	FRotator SpawnRotation;
	SpawnRotation.Yaw = 0;
	SpawnRotation.Pitch = 0;
	SpawnRotation.Roll = 0;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator<APlayerCharacter>();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forces the pawn to spawn even if colliding
	second_player = GetWorld()->SpawnActor<APlayerCharacter>(WhoToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	second_player->SpawnDefaultController();

}

void AMGPlayerController::SimulatePlayerRun()
{
	float inDeltaTime = 10000;

	FVector targetLocation = second_player->GetActorLocation();
	targetLocation.X = targetLocation.X + 100;
	auto mLocalLocation = FMath::VInterpConstantTo(
		second_player->GetActorLocation(),
		targetLocation,
		inDeltaTime,
		100
	);


	FVector targetVelocity = second_player->GetVelocity();
	targetVelocity.X = targetVelocity.X + 100;
	auto mLocalVelocity = FMath::VInterpConstantTo(
		targetVelocity,
		targetLocation,
		inDeltaTime,
		1 * 2.f
	);

	auto mLocalRotation = FMath::RInterpTo(
		second_player->GetActorRotation(),
		second_player->GetActorRotation(),
		inDeltaTime,
		1 * 8.f
	);

	auto actor_camera = second_player->GetComponentByClass(UCameraComponent::StaticClass());
	//mLocalActionPawnCameraRotation = UKismetMathLibrary::RInterpTo(
// 	auto mLocalCameraRotation = FMath::RInterpTo(
// 		RealTimeSrvPawnCamera->GetComponentRotation(),
// 		mRemotePawnTargetCameraRotation,
// 		inDeltaTime,
// 		BaseLookUpRate * 8.f
// 	);

// 	second_player->SetActorLocation(mLocalLocation);
// 	second_player->PostNetReceiveVelocity(mLocalVelocity);
// 	second_player->SetActorRotation(mLocalRotation);
	//actor_camera->SetWorldRotation(mLocalCameraRotation);

	// find out which way is forward
	const FRotator YawRotation(0, mLocalRotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	second_player->AddMovementInput(Direction, 1);


}

void AMGPlayerController::OtherPlayerEnterInsight(stPlayerStatus& newPlayerStatus)
{
	UWorld* const world = GetWorld();

	if (!world)
	{
		return;
	}

	if (newPlayerStatus.SessionId == SessionId)
	{
		return;
	}

	// 如果已经在视野范围内， 则不能再次进入
	if (InSightPlayers.find(newPlayerStatus.SessionId) != InSightPlayers.end())
	{
		return;
	}
	
	FVector SpawnLocation;
	SpawnLocation.X = newPlayerStatus.PositionX;
	SpawnLocation.Y = newPlayerStatus.PositionY;
	SpawnLocation.Z = newPlayerStatus.PositionZ;

	FRotator SpawnRotation;
	SpawnRotation.Yaw = newPlayerStatus.Yaw;
	SpawnRotation.Pitch = newPlayerStatus.Pitch;
	SpawnRotation.Roll = newPlayerStatus.Roll;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator<APlayerCharacter>();
	SpawnParams.Name = FName(*FString(std::to_string(newPlayerStatus.SessionId).c_str()));

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forces the pawn to spawn even if colliding
	APlayerCharacter* SpawnCharacter = world->SpawnActor<APlayerCharacter>(WhoToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	SpawnCharacter->SpawnDefaultController();
	SpawnCharacter->HealthValue = newPlayerStatus.HealthValue;
	SpawnCharacter->IsAttacking = false;
	SpawnCharacter->SessionID = newPlayerStatus.SessionId;
	SpawnCharacter->uuid = newPlayerStatus.SessionId;		//  暂时用 sessionID 代替


	// 添加该玩家到视野范围内
	InSightPlayers.insert(std::make_pair(newPlayerStatus.SessionId, newPlayerStatus));

}
