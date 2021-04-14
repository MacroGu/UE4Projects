// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExDataAsset.generated.h"


class UTexture;

/**
 * 
 */
UCLASS(Blueprintable)
class KBECOURSEPRO_API UExDataAsset : public UDataAsset
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere)
		TArray<UTexture*> GoodTextures;
};
