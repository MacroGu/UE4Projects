// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AbilitySystemInterface.h>
#include "BaseCharacter.generated.h"


class UAbilitySystemComponent;
class UBaseAttributeSet;
class UGameplayAbility;

UCLASS()
class GASDEMO_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBaseAttributeSet* BaseAttributeSet;


private:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获得什么技能 AbilityType 是技能类型
	UFUNCTION(BlueprintCallable)
	void GetAbility(TSubclassOf<UGameplayAbility> AbilityType);


};

