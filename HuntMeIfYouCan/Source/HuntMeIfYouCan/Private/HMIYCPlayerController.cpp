// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HMIYCPlayerController.h"
#include "NormalCharacter.h"
#include "UnrealNetwork.h"
#include "AssassinWidget.h"
#include "AssassinCharacter.h"

int32 CharacterUIOrder = 9;
int32 CommonUIOrder = 8;

AHMIYCPlayerController::AHMIYCPlayerController( const FObjectInitializer& objectInitializer ):
    Super( objectInitializer ),
    CharacterMenu( nullptr )
{
}

void AHMIYCPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis( "MoveForward", this, &AHMIYCPlayerController::OnMoveForward );
    InputComponent->BindAxis( "MoveRight", this, &AHMIYCPlayerController::OnMoveRight );

    InputComponent->BindAxis( "Turn", this, &AHMIYCPlayerController::OnTurn );
    InputComponent->BindAxis( "LookUp", this, &AHMIYCPlayerController::OnLookUp );
}

void AHMIYCPlayerController::BeginPlay()
{
    Super::BeginPlay();

    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "AHMIYCPlayerController BeginPlay" );

    AAssassinCharacter* pAssassinCharacter = Cast<AAssassinCharacter>( GetPawn() );

    if ( !IsValid( pAssassinCharacter ) )
    {
        return;
    }

    SetCharacterUI( pAssassinCharacter->GetUIPath() );
}

void AHMIYCPlayerController::OnMoveForward( float Value )
{
    ANormalCharacter* pNormalCharacter = Cast<ANormalCharacter>( GetPawn() );

    if ( nullptr == pNormalCharacter || 0.0f == Value || pNormalCharacter->IsDead() )
    {
        return;
    }

    pNormalCharacter->MoveForward( Value );
}

void AHMIYCPlayerController::OnMoveRight( float Value )
{
    ANormalCharacter* pNormalCharacter = Cast<ANormalCharacter>( GetPawn() );

    if ( nullptr == pNormalCharacter || 0.0f == Value || pNormalCharacter->IsDead() )
    {
        return;
    }

    pNormalCharacter->MoveRight( Value );
}

void AHMIYCPlayerController::OnTurn( float Value )
{
    APawn* pPawm = nullptr;

    if ( nullptr == ( pPawm = GetPawn() ) || 0.0f == Value )
    {
        return;
    }

    pPawm->AddControllerYawInput( Value );
}

void AHMIYCPlayerController::OnLookUp( float Value )
{
    APawn* pPawm = nullptr;

    if ( nullptr == ( pPawm = GetPawn() ) || 0.0f == Value )
    {
        return;
    }

    pPawm->AddControllerPitchInput( Value );
}

void AHMIYCPlayerController::StartGameNow()
{
    GetWorld()->ServerTravel( FString( "/Game/Maps/WestTown?game=/Game/Blueprints/BP_HMIYCGameMode.BP_HMIYCGameMode_C?listen" ) );
}

void AHMIYCPlayerController::SetCharacterUI( const FString& Path )
{
    if ( Path.IsEmpty() )
    {
        return;
    }

    if ( nullptr != CharacterMenu )
    {
        CharacterMenu->SetVisibility( ESlateVisibility::Hidden );
        CharacterMenu->RemoveFromViewport();
        CharacterMenu->Destruct();
    }

    UClass* WidgetClass = StaticLoadClass( UAssassinWidget::StaticClass(), nullptr, *Path );

    UAssassinWidget* Widget = CreateWidget<UAssassinWidget>( GetWorld(), WidgetClass );

    Widget->AddToViewport( CharacterUIOrder );

    Widget->SetVisibility( ESlateVisibility::Visible );

    CharacterMenu = Widget;
}
