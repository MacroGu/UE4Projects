// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SlAiPlayerAnim.h"
#include "SlAiThirdSlAiPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API USlAiThirdSlAiPlayerAnim : public USlAiPlayerAnim
{
	GENERATED_BODY()


	USlAiThirdSlAiPlayerAnim();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;


};
