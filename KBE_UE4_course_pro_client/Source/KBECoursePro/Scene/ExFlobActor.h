// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/ExActorEntity.h"
#include "ExFlobActor.generated.h"

class UStaticMeshComponent;
class UTexture;
class UMaterialInterface;
class UMaterialInstanceDynamic;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExFlobActor : public AExActorEntity
{
	GENERATED_BODY()

public:

	AExFlobActor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;
	
public:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* BaseMat;

	UPROPERTY()
		UMaterialInstanceDynamic* BaseMatInst;

	uint8 GoodId;

protected:

	virtual void BeginPlay() override;

};
