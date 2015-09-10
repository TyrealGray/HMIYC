// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssassinCharacter.h"
#include "BankRobberCharacter.generated.h"

/**
 *
 */
UCLASS()
class ABankRobberCharacter : public AAssassinCharacter
{
    GENERATED_BODY()
public:
    ABankRobberCharacter();

    virtual void BeginPlay();

    virtual void  Exposed();
};
