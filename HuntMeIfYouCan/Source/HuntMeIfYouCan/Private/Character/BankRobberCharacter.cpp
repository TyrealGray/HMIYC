// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "BankRobberCharacter.h"

ABankRobberCharacter::ABankRobberCharacter()
{

}

void ABankRobberCharacter::BeginPlay()
{
    AAssassinCharacter::BeginPlay();
    GEngine->AddOnScreenDebugMessage( -1, 4.5f, FColor::Green, "BankRobber spawn" );
}

FString ABankRobberCharacter::GetUIPath()
{
    return "";
}
