// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "AssassinsNameList.h"

AssassinsNameList* AssassinsNameList::Instance = nullptr;

AssassinsNameList::AssassinsNameList()
{
    AssassinsNameArray.Add( "BP_Archer" );
    AssassinsNameArray.Add( "BP_BankRobber" );
}

AssassinsNameList::~AssassinsNameList()
{
}

AssassinsNameList* AssassinsNameList::GetInstance()
{
    if ( nullptr == Instance )
    {
        Instance = new AssassinsNameList;
    }

    return Instance;
}

FString AssassinsNameList::GetNameByID( int32 AssassinID )
{
    return AssassinsNameArray[AssassinID];
}

int32 AssassinsNameList::GetNumberOfAssassinsType()
{
    return AssassinsNameArray.Num();
}
