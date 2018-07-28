// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlAiTypes.h"
#include "CoreMinimal.h"

/**
 * 
 */
class SLAICOURSE_API SlAiDataHandle
{
public:
	SlAiDataHandle();

	static void Initialize();

	static TSharedPtr<SlAiDataHandle> Get();

	// 修改中英文
	void ChangeLocalizationCulture(ECultureTeam Culture);
	// 修改菜单音量
	void ResetMenuVolume(float MusicVol, float SoundVol);



public:
	ECultureTeam CurrentCulture;
	float MusicVolume;	// 音量大小
	float SoundVolume;	// 音效大小
	// 存档数据
	TArray<FString> RecordDataList;

private:
	// 创建单例
	static TSharedRef<SlAiDataHandle> Create();

	// 根据enum类型获取字符串
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	// 根据字符串来获取 Enum 值
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& EnumName, FString String);

	// 初始化存档数据
	void InitRecordData();

private:
	static TSharedPtr<SlAiDataHandle> DataInstance;

};
