// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");

	RelativePath = FString("Res/ConfigData");
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (FileName.IsEmpty() || RelaPath.IsEmpty())
	{
		SlAiHelper::Debug(FString("filename or relaPath is empty") + FileName + RelaPath);
		return false;
	}

	// 获取绝对路径
	FString AbsoPath = FPaths::ProjectConfigDir() + RelaPath + FileName;
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
