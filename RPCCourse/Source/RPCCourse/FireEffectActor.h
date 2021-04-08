// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireEffectActor.generated.h"

class UParticleSystemComponent;
class UTextRenderComponent;

UCLASS()
class RPCCOURSE_API AFireEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateTimer();

	UFUNCTION()
		void OnRep_Deactivate();

protected:

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* FireEffect;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TextRender;

	UPROPERTY(Replicated)
	int32 CountDownTimer;

	FTimerHandle UpdateTimeHandle;

	UPROPERTY(ReplicatedUsing = OnRep_Deactivate)
	bool Deactivate;


};
