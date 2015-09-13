// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "NormalCharacter.h"
#include "UnrealNetwork.h"

// Sets default values
ANormalCharacter::ANormalCharacter():
    bIsNPC( false ),
    bIsDead( false )
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    bUseControllerRotationYaw = false;

    GetMesh()->SetOwnerNoSee( true );

    Camera = CreateDefaultSubobject<UCameraComponent>( TEXT( "FollowCamera" ) );
    Camera->AttachTo( RootComponent, USpringArmComponent::SocketName ); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    Camera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
    Camera->RelativeLocation = FVector( 20.0f, 0.0f, 10.0f );

    GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANormalCharacter::InitMaterial()
{
    auto HeadMat = LoadObject<UMaterial>( nullptr, TEXT( "/Game/Materials/Characters/M_Head.M_Head" ) );
    GetMesh()->SetMaterial( EMaterialInstanceIDEnum::MII_Head, HeadMat );

    auto HandMat = LoadObject<UMaterial>( nullptr, TEXT( "/Game/Materials/Characters/M_Hand.M_Hand" ) );
    GetMesh()->SetMaterial( EMaterialInstanceIDEnum::MII_Hand, HandMat );

    auto FootMat = LoadObject<UMaterial>( nullptr, TEXT( "/Game/Materials/Characters/M_Foot.M_Foot" ) );
    GetMesh()->SetMaterial( EMaterialInstanceIDEnum::MII_Foot, FootMat );

    auto BodyMat = LoadObject<UMaterial>( nullptr, TEXT( "/Game/Materials/Characters/M_Body.M_Body" ) );
    GetMesh()->SetMaterial( EMaterialInstanceIDEnum::MII_Body, BodyMat );

    MeshMaterialInstances.Add( GetMesh()->CreateAndSetMaterialInstanceDynamic( EMaterialInstanceIDEnum::MII_Head ) );
    MeshMaterialInstances.Add( GetMesh()->CreateAndSetMaterialInstanceDynamic( EMaterialInstanceIDEnum::MII_Hand ) );
    MeshMaterialInstances.Add( GetMesh()->CreateAndSetMaterialInstanceDynamic( EMaterialInstanceIDEnum::MII_Foot ) );
    MeshMaterialInstances.Add( GetMesh()->CreateAndSetMaterialInstanceDynamic( EMaterialInstanceIDEnum::MII_Body ) );
}

// Called when the game starts or when spawned
void ANormalCharacter::BeginPlay()
{
    Super::BeginPlay();

    InitMaterial();

    RandomMeshTexture();
}

// Called every frame
void ANormalCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ANormalCharacter::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
    Super::SetupPlayerInputComponent( InputComponent );
}

void ANormalCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps( OutLifetimeProps );

    DOREPLIFETIME( ANormalCharacter, bIsDead );
    DOREPLIFETIME( ANormalCharacter, bIsNPC );
}

void ANormalCharacter::MoveForward( float Value )
{
    // find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation( 0, Rotation.Yaw, 0 );

    // get forward vector
    const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
    AddMovementInput( Direction, Value );
}

void ANormalCharacter::MoveRight( float Value )
{
    // find out which way is right
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation( 0, Rotation.Yaw, 0 );

    // get right vector
    const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
    // add movement in that direction
    AddMovementInput( Direction, Value );
}

void ANormalCharacter::SetIsNPC( bool IsNPC )
{
    bIsNPC = IsNPC;
    // If this next check succeeds, we are *not* the authority, meaning we are a network client.
    // In this case we also want to call the server function to tell it to change the bSomeBool property as well.
    if ( Role < ROLE_Authority )
    {
        ServerSetIsNPC( IsNPC );
    }
}

void ANormalCharacter::SetDead( bool IsDead )
{
    bIsDead = IsDead;

    // If this next check succeeds, we are *not* the authority, meaning we are a network client.
    // In this case we also want to call the server function to tell it to change the bSomeBool property as well.
    if ( Role < ROLE_Authority )
    {
        ServerSetDead( IsDead );
    }
}

void ANormalCharacter::ServerSetDead_Implementation( bool IsDead )
{
    SetDead( IsDead );
}

bool ANormalCharacter::ServerSetDead_Validate( bool IsDead )
{
    return true;
}

void ANormalCharacter::ServerSetIsNPC_Implementation( bool IsNPC )
{
    SetIsNPC( IsNPC );
}

bool ANormalCharacter::ServerSetIsNPC_Validate( bool IsNPC )
{
    return true;
}

TArray<UMaterialInstanceDynamic*> ANormalCharacter::GetMeshMaterialInstances()
{
    return MeshMaterialInstances;
}

bool ANormalCharacter::OnPlayerHit()
{
    SetDead( true );

    GEngine->AddOnScreenDebugMessage( -1, 3.0, FColor::Green, GetName() + " OnPlayerHit!" );

    return false;
}

bool ANormalCharacter::IsDead()
{
    return bIsDead;
}

void ANormalCharacter::RandomMeshTexture()
{
    auto MeshMaterialInstances = GetMeshMaterialInstances();

    auto MeshTexture = LoadObject<UTexture2D>( nullptr, TEXT( "/Game/Textures/UnknowTexture.UnknowTexture" ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue(
        FName( "ManHeadTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue(
        FName( "ManHandTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue(
        FName( "ManFootTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue(
        FName( "ManBodyTextureParameter" ), MeshTexture );
}
