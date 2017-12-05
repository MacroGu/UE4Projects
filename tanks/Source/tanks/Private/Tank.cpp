// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);  // Àƒ…·ŒÂ»Î
	int32 DamageToApply = FMath::Clamp<int>(DamagePoint, 0, CurrentHp);

	CurrentHp -= DamageToApply; 

	if (CurrentHp <= 0)
	{
		// Tank died
		// UE_LOG(LogTemp, Warning, TEXT("Tank dead, Tank name: %s"), *GetName());
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercentage()
{
	return (float) CurrentHp / MaxHp;
}

void ATank::ResetHealth()
{
	CurrentHp = MaxHp;
}

