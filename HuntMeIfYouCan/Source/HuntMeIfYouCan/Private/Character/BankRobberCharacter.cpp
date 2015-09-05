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

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue( FName( "ManHeadTextureParameter" ),
            LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Materials/Characters/Assassin/BankRobber/T_Head.T_Head" ) ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue( FName( "ManHandTextureParameter" ),
            LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Materials/Characters/Assassin/BankRobber/T_Hand.T_Hand" ) ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue( FName( "ManFootTextureParameter" ),
            LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Materials/Characters/Assassin/BankRobber/T_Foot.T_Foot" ) ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue( FName( "ManBodyTextureParameter" ),
            LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Materials/Characters/Assassin/BankRobber/T_Body.T_Body" ) ) );
}
