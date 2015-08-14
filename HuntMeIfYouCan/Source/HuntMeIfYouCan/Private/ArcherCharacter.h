// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssassinCharacter.h"
#include "ArcherCharacter.generated.h"

/**
 *
 */
UCLASS()
class AArcherCharacter : public AAssassinCharacter
{
    GENERATED_BODY()
public:

    AArcherCharacter();

private:

    virtual void UseConcealedItem();

};
