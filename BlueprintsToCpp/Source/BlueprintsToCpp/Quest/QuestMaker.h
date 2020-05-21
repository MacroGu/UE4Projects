// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "QuestMaker.generated.h"

UCLASS()
class BLUEPRINTSTOCPP_API AQuestMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestMaker();

	UFUNCTION(BlueprintCallable)
	void RefreshVisibility();


protected:
	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	AQuestManager* GetQuestManager() const;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ShowAtProgress = 0;
};
