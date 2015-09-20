// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HMIYCPlayerController.h"
#include "NormalCharacter.h"
#include "UnrealNetwork.h"


AHMIYCPlayerController::AHMIYCPlayerController( const FObjectInitializer& objectInitializer ):
    Super( objectInitializer )
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
