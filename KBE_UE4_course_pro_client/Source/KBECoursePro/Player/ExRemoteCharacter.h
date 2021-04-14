// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ExCharacterEntity.h"
#include "ExRemoteCharacter.generated.h"


class UBoxComponent;
class UWidgetComponent;
class UExBloodBar;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExRemoteCharacter : public AExCharacterEntity
{
	GENERATED_BODY()
	
public:

	AExRemoteCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

public:

	// 判断是否着地碰撞体
	UPROPERTY(EditAnywhere)
		UBoxComponent* GroundBox;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* BloodBarComponent;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	UExBloodBar* BloodBar;

	static FName GroundName;

};
