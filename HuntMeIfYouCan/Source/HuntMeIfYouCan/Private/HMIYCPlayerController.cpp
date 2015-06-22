// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HMIYCPlayerController.h"
#include "NormalCharacter.h"


AHMIYCPlayerController::AHMIYCPlayerController(const FObjectInitializer& objectInitializer):
    Super(objectInitializer)
{

}

void AHMIYCPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AHMIYCPlayerController::onMoveForward);
    InputComponent->BindAxis("MoveRight", this, &AHMIYCPlayerController::onMoveRight);

    InputComponent->BindAxis("Turn", this, &AHMIYCPlayerController::onTurn);
    InputComponent->BindAxis("LookUp", this, &AHMIYCPlayerController::onLookUp);
}

void AHMIYCPlayerController::onMoveForward(float Value)
{
    ANormalCharacter* pNormalCharacter = Cast<ANormalCharacter>(GetPawn());

    if (nullptr == pNormalCharacter || 0.0f == Value)
    {
        return;
    }

    pNormalCharacter->MoveForward(Value);
}

void AHMIYCPlayerController::onMoveRight(float Value)
{
    ANormalCharacter* pNormalCharacter = Cast<ANormalCharacter>(GetPawn());

    if (nullptr == pNormalCharacter || 0.0f == Value)
    {
        return;
    }

    pNormalCharacter->MoveRight(Value);
}

void AHMIYCPlayerController::onTurn(float Value)
{
    APawn* pPawm = nullptr;

    if (nullptr == (pPawm = GetPawn()) || 0.0f == Value)
    {
        return;
    }

    pPawm->AddControllerYawInput(Value);
}

void AHMIYCPlayerController::onLookUp(float Value)
{
    APawn* pPawm = nullptr;

    if (nullptr == (pPawm = GetPawn()) || 0.0f == Value)
    {
        return;
    }

    pPawm->AddControllerPitchInput(Value);
}
