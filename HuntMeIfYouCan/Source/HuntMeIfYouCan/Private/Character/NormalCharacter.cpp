// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "NormalCharacter.h"
#include "../CivilianPropertyManager.h"
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
    DOREPLIFETIME( ANormalCharacter, TexturesGroupID );
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
    ServerSetIsNPC( IsNPC );
}

void ANormalCharacter::ServerSetIsNPC_Implementation( bool IsNPC )
{
    bIsNPC = IsNPC;
}

bool ANormalCharacter::ServerSetIsNPC_Validate( bool IsNPC )
{
    return ( Role >= ROLE_Authority );
}

void ANormalCharacter::SetDead( bool IsDead )
{
    ServerSetDead( IsDead );
}

void ANormalCharacter::ServerSetDead_Implementation( bool IsDead )
{
    bIsDead = IsDead;
}

bool ANormalCharacter::ServerSetDead_Validate( bool IsDead )
{
    return ( Role >= ROLE_Authority );
}

void ANormalCharacter::SetTexturesGroupID( int32 ID )
{
    ServerSetTexturesGroupID( ID );
}

void ANormalCharacter::ServerSetTexturesGroupID_Implementation( int32 ID )
{
    TexturesGroupID = ID;
}

bool ANormalCharacter::ServerSetTexturesGroupID_Validate( int32 ID )
{
    return ( Role >= ROLE_Authority );
}

TArray<UMaterialInstanceDynamic*> ANormalCharacter::GetMeshMaterialInstances()
{
    return MeshMaterialInstances;
}

bool ANormalCharacter::OnPlayerHit( class AAssassinCharacter *Assassin /*= nullptr*/ )
{
    SetDead( true );

    if ( NULL != DeadSound )
    {
        UGameplayStatics::PlaySoundAtLocation( this, DeadSound, GetActorLocation() );
    }

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

    int32 ID = CivilianPropertyManager::GetInstance()->GetRandomTextureGroupID();

    SetTexturesGroupID( ID );

    auto TexturesGroup = CivilianPropertyManager::GetInstance()->GetRandomTexturesByID( TexturesGroupID );

    if ( 0 == TexturesGroup.Num() )
    {
        UseUnknowTexture();
        return;
    }

    SetRandomMeshTexture( TexturesGroup );
}

void ANormalCharacter::UseUnknowTexture()
{
    auto MeshTexture = CivilianPropertyManager::GetInstance()->GetUnknowTexture();

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue(
        FName( "ManHeadTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue(
        FName( "ManHandTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue(
        FName( "ManFootTextureParameter" ), MeshTexture );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue(
        FName( "ManBodyTextureParameter" ), MeshTexture );
}

void ANormalCharacter::SetRandomMeshTexture( const TArray<UTexture2D*> &Textures )
{
    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue(
        FName( "ManHeadTextureParameter" ), Textures[EMaterialInstanceIDEnum::MII_Head] );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue(
        FName( "ManHandTextureParameter" ), Textures[EMaterialInstanceIDEnum::MII_Hand] );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue(
        FName( "ManFootTextureParameter" ), Textures[EMaterialInstanceIDEnum::MII_Foot] );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue(
        FName( "ManBodyTextureParameter" ), Textures[EMaterialInstanceIDEnum::MII_Body] );
}
