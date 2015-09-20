// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HMIYCPlayerController.generated.h"

/**
 *
 */
UCLASS()
class HUNTMEIFYOUCAN_API AHMIYCPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AHMIYCPlayerController( const FObjectInitializer& objectInitializer );

    virtual void SetupInputComponent() override;

    UFUNCTION( BlueprintCallable, category = "StartGame" )
    void StartGameNow();

private:

    void OnMoveForward( float Value );
    void OnMoveRight( float Value );

    void OnTurn( float Value );
    void OnLookUp( float Value );

};
