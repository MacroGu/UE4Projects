// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include <AbilitySystemComponent.h>
#include "BaseAttributeSet.h"
#include <GameplayAbilitySpec.h>

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ABaseCharacter::GetAbility(TSubclassOf<UGameplayAbility> AbilityType)
{
	if (nullptr != AbilityType && nullptr != AbilitySystemComp)
	{
		AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityType));
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

