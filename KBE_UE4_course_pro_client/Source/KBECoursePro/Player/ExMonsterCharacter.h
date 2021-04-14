// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ExCharacterEntity.h"
#include "ExMonsterCharacter.generated.h"


class UWidgetComponent;
class UExBloodBar;
/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExMonsterCharacter : public AExCharacterEntity
{
	GENERATED_BODY()
	
public:

	AExMonsterCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

	void PlayDeath();

public:

	UPROPERTY(EditAnywhere)
		UWidgetComponent* BloodBarComponent;

protected:

	virtual void BeginPlay() override;

	void MonsterDestroy();

protected:

	// UPROPERTY()
		UExBloodBar* BloodBar;

	FTimerHandle DestroyHandle;

};
