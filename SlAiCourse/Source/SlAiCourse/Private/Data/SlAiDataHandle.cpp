// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "Internationalization.h"
#include "SlAiSingleton.h"
#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"


TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle());
	return DataRef;
}

SlAiDataHandle::SlAiDataHandle()
{
	// 初始化 存档数据 
	InitRecordData();
}


void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	default:
		break;
	}

	// 赋值
	CurrentCulture = Culture;
	// 更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
	}

	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
	}
	// 更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}

	return EnumPtr->GetNameStringByIndex((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& EnumName, FString String)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if (!EnumPtr)
	{
		return TEnum(0);
	}

	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(String)));
}

void SlAiDataHandle::InitRecordData()
{
	RecordName = FString("");

	// 获取语言
	FString Culture;
	// 读取存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	// 初始化语言
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	// 输出一下
	SlAiHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume));
	// 循环读取 RecordDataList
	for (TArray<FString>::TIterator It(RecordDataList); It; ++It)
	{
		SlAiHelper::Debug(*It, 20.f);
	}

}
