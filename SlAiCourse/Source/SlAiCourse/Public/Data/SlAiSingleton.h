// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class SLAICOURSE_API SlAiSingleton
{
public:
	static TSharedPtr<T> Get();

private:
	static void Initialize();

	static TSharedPtr<T> Create();

private:

	static TSharedPtr<T> TInstance;

};
