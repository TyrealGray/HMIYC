// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
/**
 *
 */
class HUNTMEIFYOUCAN_API SpawnerManager
{
public:
    SpawnerManager();
    ~SpawnerManager();

private:
    TArray<class ACivilianSpawner*> CivilianSpawners;
};
