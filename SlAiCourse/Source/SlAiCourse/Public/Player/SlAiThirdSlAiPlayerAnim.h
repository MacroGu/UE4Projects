// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SlAiPlayerAnim.h"
#include "SlAiHelper.h"
#include "ConstructorHelpers.h"
#include "SlAiThirdSlAiPlayerAnim.generated.h"


/**
 * 
 */
UCLASS()
class SLAICOURSE_API USlAiThirdSlAiPlayerAnim : public USlAiPlayerAnim
{
	GENERATED_BODY()


public:
	USlAiThirdSlAiPlayerAnim();

protected:
	// 重写更新属性方法
	virtual void UpdateParameter() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;


};
