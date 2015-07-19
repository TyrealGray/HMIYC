// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
/**
 *
 */
class HUNTMEIFYOUCAN_API CivilianSpawnerManager
{
public:
    CivilianSpawnerManager();
    ~CivilianSpawnerManager();

    static CivilianSpawnerManager* GetInstance();

    int32 GetNumberOfCivilianNeed();

    void CivilianRespawn();

    void SetCivilianSpawners( TArray<class ACivilianSpawner*> SpawnerArray );

private:
    static CivilianSpawnerManager* SpawnerManagerInstance;

    int32 CivilianSpawnNumber;

    TArray<class ACivilianSpawner*> CivilianSpawners;
};
