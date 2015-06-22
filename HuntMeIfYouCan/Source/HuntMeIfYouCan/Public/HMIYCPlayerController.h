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
    AHMIYCPlayerController(const FObjectInitializer& objectInitializer);

    virtual void SetupInputComponent() override;

private:

    void onMoveForward(float Value);
    void onMoveRight(float Value);

    void onTurn(float Value);
    void onLookUp(float Value);

};
