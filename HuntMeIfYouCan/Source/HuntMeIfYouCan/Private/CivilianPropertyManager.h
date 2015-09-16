// GPLv2

#pragma once
#include "Engine.h"

/**
 *
 */
class CivilianPropertyManager
{
public:

    static CivilianPropertyManager* GetInstance();

    TArray<UTexture2D*> GetRandomTexturesByID( int32 GroupID );

    UTexture2D* GetUnknowTexture();

    int32 GetRandomTextureGroupID();

private:
    static CivilianPropertyManager* Instance;

    CivilianPropertyManager();
    ~CivilianPropertyManager();

    TArray<TArray<UTexture2D*>> MeshTextureGroup;

    UTexture2D* UnknowTexture;

    void InitRandomMeshTextures();
};
