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

    TArray<UTexture2D*> GetRandomTextures();

private:
    static CivilianPropertyManager* Instance;

    CivilianPropertyManager();
    ~CivilianPropertyManager();

    TArray<TArray<UTexture2D*>> MeshTextureGroup;

    void InitRandomMeshTextures();
};
