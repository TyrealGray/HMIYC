// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NormalCharacter.generated.h"

UCLASS()
class HUNTMEIFYOUCAN_API ANormalCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ANormalCharacter();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaTime ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;

    virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;

public:

    void MoveForward( float Value );

    void MoveRight( float Value );

    UFUNCTION( BlueprintCallable, Category = Action )
    void SetDead( bool IsDead );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetDead( bool IsDead );
    virtual void ServerSetDead_Implementation( bool IsDead );
    virtual bool ServerSetDead_Validate( bool IsDead );

    void SetIsNPC( bool IsNPC );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetIsNPC( bool IsNPC );
    virtual void ServerSetIsNPC_Implementation( bool IsNPC );
    virtual bool ServerSetIsNPC_Validate( bool IsNPC );

private:

    /** Follow camera */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
    class UCameraComponent * Camera;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsNPC;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsDead;
};
