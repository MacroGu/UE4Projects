// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"
#include "JsonSerializerMacros.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	ObjectAttrFileName = FString("ObjectAttribute.json");
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

TSharedPtr<FJsonObject> SlAiJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>>  BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;
	
	for (int i = 0; i < RecordDataList->Num(); ++i)
	{
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}

	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObject->SetArrayField("T", BaseDataArray);

	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

//	SlAiHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	// 去掉多余的字符
	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));

//	SlAiHelper::Debug(FString("final Str : " + JsonStr), 60.f);

	// 写入文件
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);

	return JsonObject;
}

void SlAiJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); ++i)
		{
			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			FText EN = FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr = ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack = ObjectAttr[3]->AsObject()->GetIntegerField("PlantAttack");
			int MetalAttack = ObjectAttr[4]->AsObject()->GetIntegerField("MetalAttcck");
			int AnimalAttack = ObjectAttr[5]->AsObject()->GetIntegerField("AnimalAttack");
			int AffectRange = ObjectAttr[6]->AsObject()->GetIntegerField("AffectRange");
			FString TexPath = ObjectAttr[7]->AsObject()->GetStringField("TexPath");

			EObjectType::Type ObjectType = StringToObjectType(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr = MakeShareable(new ObjectAttribute(EN, ZH, ObjectType, PlantAttack, MetalAttack, AnimalAttack, AffectRange, TexPath));

			ObjectAttrMap.Add(i, ObjectAttrPtr);
		}
	}
	else
	{
		SlAiHelper::Debug(FString("Deserialize Failed!"));
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

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (!JsonObj.IsValid())
	{
		SlAiHelper::Debug(FString(" jsonObj is null or jsonStr is empty "));
		return false;
	}

	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
	FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);

	return true;
}

bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (FileName.IsEmpty() || RelaPath.IsEmpty() || FileName.IsEmpty())
	{
		SlAiHelper::Debug(FString("filename or relaPath is empty") + FileName + RelaPath);
		return false;
	}

	FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
	// 保存
	if (!FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))
	{
		SlAiHelper::Debug(FString("save file failed! ") + FileName + RelaPath);
		return false;
	}

	return true;
}

EObjectType::Type SlAiJsonHandle::StringToObjectType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;
	if (ArgStr.Equals(FString("Food"))) return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool"))) return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon"))) return EObjectType::Weapon;

	return EObjectType::Normal;
}
