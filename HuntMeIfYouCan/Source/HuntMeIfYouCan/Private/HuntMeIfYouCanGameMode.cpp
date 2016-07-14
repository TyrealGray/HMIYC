// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HuntMeIfYouCanGameMode.h"
#include "GamePlayHUD.h"

AHuntMeIfYouCanGameMode::AHuntMeIfYouCanGameMode( const FObjectInitializer& objectInitializer ):
    Super( objectInitializer )
{
    HUDClass = AGamePlayHUD::StaticClass();
}
