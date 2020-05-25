// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTriggerPick.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class BLUEPRINTSTOCPP_API UQuestTriggerPick : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestTriggerPick();

	UFUNCTION(BlueprintCallable)
	void PickUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;




protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName QuestId = "None";


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
