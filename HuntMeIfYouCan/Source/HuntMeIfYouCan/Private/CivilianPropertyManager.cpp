// GPLv2

#include "HuntMeIfYouCan.h"
#include "CivilianPropertyManager.h"

const int32 NUMBER_OF_CIVILIANS_TYPE = 2;

CivilianPropertyManager* CivilianPropertyManager::Instance = nullptr;

CivilianPropertyManager::CivilianPropertyManager()
{
}

CivilianPropertyManager::~CivilianPropertyManager()
{
}

CivilianPropertyManager* CivilianPropertyManager::GetInstance()
{
    if ( nullptr == Instance )
    {
        Instance = new CivilianPropertyManager;
        Instance->InitRandomMeshTextures();

    }
    return Instance;
}

void CivilianPropertyManager::InitRandomMeshTextures()
{
    TArray<UTexture2D*> MeshTextures;
    FString TexturePath;

    for ( int32 index = 0; index < NUMBER_OF_CIVILIANS_TYPE; ++index )
    {
        TexturePath = "/Game/Textures/Characters/Civilians/" + FString::FromInt( index ) + "/T_Civilian_Head.T_Civilian_Head";
        MeshTextures.Add( LoadObject<UTexture2D>( nullptr, *TexturePath ) );

        TexturePath = "/Game/Textures/Characters/Civilians/" + FString::FromInt( index ) + "/T_Civilian_Hand.T_Civilian_Hand";
        MeshTextures.Add( LoadObject<UTexture2D>( nullptr, *TexturePath ) );

        TexturePath = "/Game/Textures/Characters/Civilians/" + FString::FromInt( index ) + "/T_Civilian_Foot.T_Civilian_Foot";
        MeshTextures.Add( LoadObject<UTexture2D>( nullptr, *TexturePath ) );

        TexturePath = "/Game/Textures/Characters/Civilians/" + FString::FromInt( index ) + "/T_Civilian_Body.T_Civilian_Body";
        MeshTextures.Add( LoadObject<UTexture2D>( nullptr, *TexturePath ) );

        MeshTextureGroup.Add( MeshTextures );

        MeshTextures.Empty();
    }

    UnknowTexture = LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Textures/UnknowTexture.UnknowTexture" ) );
}

TArray<UTexture2D*> CivilianPropertyManager::GetRandomTexturesByID( int32 GroupID )
{
    TArray<UTexture2D*> NoneArray;

    return ( 0 == MeshTextureGroup.Num() ) ? NoneArray : MeshTextureGroup[GroupID];
}

int32 CivilianPropertyManager::GetRandomTextureGroupID()
{
    return FMath::FRandRange( 0, NUMBER_OF_CIVILIANS_TYPE );
}

UTexture2D* CivilianPropertyManager::GetUnknowTexture()
{
    return UnknowTexture;
}
