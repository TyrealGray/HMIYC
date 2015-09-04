// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "CivilianSpawnerManager.h"
#include "CivilianSpawner.h"

CivilianSpawnerManager* CivilianSpawnerManager::SpawnerManagerInstance = nullptr;

CivilianSpawnerManager::CivilianSpawnerManager() :
    CivilianSpawnNumber( 60 )
{

}

CivilianSpawnerManager::~CivilianSpawnerManager()
{
}

CivilianSpawnerManager* CivilianSpawnerManager::GetInstance()
{
    if ( nullptr == SpawnerManagerInstance )
    {
        SpawnerManagerInstance = new CivilianSpawnerManager();
    }

    return SpawnerManagerInstance;
}

int32 CivilianSpawnerManager::GetNumberOfCivilianNeed()
{
    return CivilianSpawnNumber;
}

void CivilianSpawnerManager::CivilianRespawn()
{
    if ( 0 == CivilianSpawners.Num() )
    {
        return;
    }

    int32 SpawnerNo = FMath::RandRange( 0, CivilianSpawners.Num() - 1 );

    ACivilianSpawner* Spawner = CivilianSpawners[SpawnerNo];

    if ( Spawner->IsPendingKill() )
    {
        return;
    }

    if ( !Spawner->IsInit() )
    {
        Spawner->Init();
    }

    Spawner->SpawnCivilian();
}

void CivilianSpawnerManager::SetCivilianSpawners( TArray<class ACivilianSpawner*> SpawnerArray )
{
    CivilianSpawners = SpawnerArray;
}

