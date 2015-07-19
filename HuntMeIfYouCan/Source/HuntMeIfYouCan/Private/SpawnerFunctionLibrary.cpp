// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "SpawnerFunctionLibrary.h"
#include "CivilianSpawnerManager.h"
#include "CivilianSpawner.h"

void USpawnerFunctionLibrary::InitSpawnerManager( TArray<class ACivilianSpawner*> SpawnerArray )
{
    CivilianSpawnerManager* ManagerInstance = CivilianSpawnerManager::GetInstance();
    ManagerInstance->SetCivilianSpawners( SpawnerArray );

    int32 NumberOfCivilians = ManagerInstance->GetNumberOfCivilianNeed();

    for ( int32 Index = 0; Index < NumberOfCivilians; ++Index )
    {
        ManagerInstance->CivilianRespawn();
    }

}

void USpawnerFunctionLibrary::CivilianRespawn()
{
    CivilianSpawnerManager::GetInstance()->CivilianRespawn();
}
