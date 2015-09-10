// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "BankRobberCharacter.h"

ABankRobberCharacter::ABankRobberCharacter()
{

}

void ABankRobberCharacter::Exposed()
{
    AAssassinCharacter::Exposed();

    auto MeshMaterialInstances = GetMeshMaterialInstances();

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue(
        FName( "ManHeadTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Head ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue(
        FName( "ManHandTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Hand ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue(
        FName( "ManFootTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Foot ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue(
        FName( "ManBodyTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Body ) );
}

void ABankRobberCharacter::BeginPlay()
{
    AAssassinCharacter::BeginPlay();
    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "BankRobber spawn" );
}
