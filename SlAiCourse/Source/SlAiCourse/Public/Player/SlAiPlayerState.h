// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SlAiTypes.h"
#include "SlAiPlayerState.generated.h"

class STextBlock;

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASlAiPlayerState();
	
	// 提供给ShortcutWdiget的添加快捷栏容器委托
	void RegistyerShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);
	

private:
	// 获取快捷栏物品信息
	FText GetShortcutInfoText() const;

private:
	
	// 快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	// 快捷栏信息参数
	TAttribute<FText> ShortcutInfoTextAttr;

};
