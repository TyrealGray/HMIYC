// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NormalCharacter.generated.h"

enum EMaterialInstanceIDEnum
{
    MII_Head = 0,
    MII_Hand,
    MII_Foot,
    MII_Body
};

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

    virtual bool OnPlayerHit( class AAssassinCharacter *Assassin = nullptr );

    bool IsDead();

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

    void SetTexturesGroupID( int32 ID );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetTexturesGroupID( int32 ID );
    virtual void ServerSetTexturesGroupID_Implementation( int32 ID );
    virtual bool ServerSetTexturesGroupID_Validate( int32 ID );

    void RandomMeshTexture();

    void SetRandomMeshTexture( const TArray<UTexture2D*> &Textures );

    TArray<UMaterialInstanceDynamic*> GetMeshMaterialInstances();

private:

    /** Follow camera */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
    class UCameraComponent * Camera;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsNPC;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsDead;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = MeshTexture, meta = ( AllowPrivateAccess = "true" ) )
    int32 TexturesGroupID;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay, meta = ( AllowPrivateAccess = "true" ) )
    class USoundBase * DeadSound;

    TArray<UMaterialInstanceDynamic*> MeshMaterialInstances;

    TArray<TArray<UTexture2D*>> MeshTextureGroup;

    void InitMaterial();

    void UseUnknowTexture();
};
