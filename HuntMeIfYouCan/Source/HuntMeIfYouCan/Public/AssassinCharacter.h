// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NormalCharacter.h"
#include "AssassinCharacter.generated.h"

/**
 *
 */
UCLASS()
class HUNTMEIFYOUCAN_API AAssassinCharacter : public ANormalCharacter
{
    GENERATED_BODY()
public:
    // Sets default values for this character's properties
    AAssassinCharacter();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaTime ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetSomeBool( bool bNewSomeBool );

    void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;

    void SetSomeBool( bool bNewSomeBool );
    virtual void ServerSetSomeBool_Implementation( bool bNewSomeBool );
    virtual bool ServerSetSomeBool_Validate( bool bNewSomeBool );

    UFUNCTION( BlueprintCallable, Category = Action )
    void SetStab( bool IsStab );

private:
    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsStab;

    bool bSomeBool;

    void UseSkill();
};
