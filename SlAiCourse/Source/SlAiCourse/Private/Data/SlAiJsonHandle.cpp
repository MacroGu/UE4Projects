// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");

	RelativePath = FString("Res/ConfigData/");
}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	if (!LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue))
	{
		SlAiHelper::Debug("load file failed!");
		return;
	}

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		SlAiHelper::Debug(FString("Deserialize Failed!"));
	}
	// 获取解析数据
	Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
	MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
	SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
	// 获取存档数据
	TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
	for (int i = 0; i < RecordDataArray.Num(); ++i)
	{
		FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
		RecordDataList.Add(RecordDataName);
	}
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (FileName.IsEmpty() || RelaPath.IsEmpty())
	{
		SlAiHelper::Debug(FString("filename or relaPath is empty") + FileName + RelaPath);
		return false;
	}

	// 获取绝对路径
	FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
	if (!FPaths::FileExists(AbsoPath))
	{
		// 加载不成功
		SlAiHelper::Debug(FString("Load Error") + AbsoPath);
		return false;
	}


	if (!FFileHelper::LoadFileToString(ResultString, *AbsoPath))
	{
		// 输出文件不存在
		SlAiHelper::Debug(FString("File Not Exist") + AbsoPath);
		return false;
	}

	return true;
}
