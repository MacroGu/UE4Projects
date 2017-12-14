// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpHealth.h"
#include "Tank.h"


void APickUpHealth::UseItem(AActor* User)
{
	Super::UseItem(User);
	ATank* UserTank = Cast<ATank>(User);
	UserTank->AddTankHealth(HealtToAdd);

}
