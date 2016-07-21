// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "ArcherCharacter.h"
#include "AssassinWidget.h"
#include "HMIYCGameInstance.h"

AArcherCharacter::AArcherCharacter()
{

}

void AArcherCharacter::BeginPlay()
{
    AAssassinCharacter::BeginPlay();
    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "Archer spawn" );
}

void AArcherCharacter::OpenUI()
{
    if ( !IsValid( CharacterMenu ) )
    {
        UUserWidget* UIMenu = Cast<UHMIYCGameInstance>( GetGameInstance() )->CreateUIWidget( "/Game/Blueprints/Widgets/Characters/ArcherUI.ArcherUI_C" );
        CharacterMenu = Cast<UAssassinWidget>( UIMenu );
    }

    CharacterMenu->SetVisibility( ESlateVisibility::Visible );

    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "Archer OpenUI" );
}

class UAssassinWidget* AArcherCharacter::GetUI()
{
    if ( !IsValid( CharacterMenu ) )
    {
        UUserWidget* UIMenu = Cast<UHMIYCGameInstance>( GetGameInstance() )->CreateUIWidget( "/Game/Blueprints/Widgets/Characters/ArcherUI.ArcherUI_C" );
        CharacterMenu = Cast<UAssassinWidget>( UIMenu );
    }

    return CharacterMenu;
}
