// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HMIYCGameInstance.h"

const int32 UI_ZORDER = 10;
UHMIYCGameInstance::UHMIYCGameInstance( const FObjectInitializer &objectInitializer ):
    Super( objectInitializer ),
    MainMenu( nullptr ),
    ServerList( nullptr ),
    PauseMenu( nullptr )
{

}

void UHMIYCGameInstance::OpenMainMenu()
{
    if ( !IsValid( MainMenu ) )
    {
        MainMenu = CreateUIWidget( "/Game/Blueprints/Widgets/MainMenu.MainMenu_C" );
    }

    if ( IsValid( ServerList ) && ServerList->IsVisible() )
    {
        ServerList->SetVisibility( ESlateVisibility::Hidden );
    }

    MainMenu->SetVisibility( ESlateVisibility::Visible );
}

void UHMIYCGameInstance::OpenServerList()
{
    if ( !IsValid( ServerList ) )
    {
        ServerList = CreateUIWidget( "/Game/Blueprints/Widgets/ServerList.ServerList_C" );
    }

    if ( IsValid( MainMenu ) && MainMenu->IsVisible() )
    {
        MainMenu->SetVisibility( ESlateVisibility::Hidden );
    }
    ServerList->SetVisibility( ESlateVisibility::Visible );
}

void UHMIYCGameInstance::OpenPauseMenu()
{
    if ( !IsValid( PauseMenu ) )
    {
        PauseMenu = CreateUIWidget( "/Game/Blueprints/Widgets/PauseMenu.PauseMenu_C" );
    }

    PauseMenu->SetVisibility( ESlateVisibility::Visible );
}

class UUserWidget* UHMIYCGameInstance::CreateUIWidget( const FString& Path )
{
    UClass* WidgetClass = StaticLoadClass( UUserWidget::StaticClass(), nullptr, *Path );

    UUserWidget* Widget = CreateWidget<UUserWidget>( GetWorld(), WidgetClass );

    Widget->AddToViewport( UI_ZORDER );

    Widget->SetVisibility( ESlateVisibility::Hidden );

    return Widget;
}
