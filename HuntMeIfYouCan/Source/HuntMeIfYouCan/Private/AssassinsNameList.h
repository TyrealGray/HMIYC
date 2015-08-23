// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"

/**
 *
 */
class AssassinsNameList
{
public:
    static AssassinsNameList* GetInstance();

    FString GetNameByID( int32 AssassinID );

    int32 GetNumberOfAssassinsType();

private:
    static AssassinsNameList* Instance;

    TArray<FString> AssassinsNameArray;

    AssassinsNameList();
    ~AssassinsNameList();
};
