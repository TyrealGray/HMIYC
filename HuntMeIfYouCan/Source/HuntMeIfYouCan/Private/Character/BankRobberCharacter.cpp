// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "BankRobberCharacter.h"
#include "AssassinWidget.h"

ABankRobberCharacter::ABankRobberCharacter()
{

}

void ABankRobberCharacter::BeginPlay()
{
    AAssassinCharacter::BeginPlay();
    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "BankRobber spawn" );
}

void ABankRobberCharacter::OpenUI()
{

}

class UAssassinWidget* ABankRobberCharacter::GetUI()
{
    return nullptr;
}
