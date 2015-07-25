// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "AssassinCharacter.h"
#include "UnrealNetwork.h"

AAssassinCharacter::AAssassinCharacter()
{
    bIsStab = false;
}

void AAssassinCharacter::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentHuntSkill( EHuntSkillEnum::HSE_ConcealedItem );
}

void AAssassinCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

void AAssassinCharacter::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
    Super::SetupPlayerInputComponent( InputComponent );

    InputComponent->BindAction( "Jump", IE_Pressed, this, &ACharacter::Jump );
    InputComponent->BindAction( "Jump", IE_Released, this, &ACharacter::StopJumping );

    InputComponent->BindAction( "UseSkill", IE_Pressed, this, &AAssassinCharacter::UseSkill );

    InputComponent->BindAction( "ConcealedItem", IE_Pressed, this, &AAssassinCharacter::SwitchConcealedItem );
    InputComponent->BindAction( "TargetItem", IE_Pressed, this, &AAssassinCharacter::SwitchTargetItem );
}

void AAssassinCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps( OutLifetimeProps );

    DOREPLIFETIME( AAssassinCharacter, bIsStab );
    DOREPLIFETIME( AAssassinCharacter, CurrentStatus );
    DOREPLIFETIME( AAssassinCharacter, CurrentHuntSkill );
    DOREPLIFETIME( AAssassinCharacter, CurrentRunningSkill );
}

void AAssassinCharacter::UseSkill()
{
    switch ( CurrentHuntSkill )
    {
    case EHuntSkillEnum::HSE_ConcealedItem:
        SetStab( true );
        break;
    case EHuntSkillEnum::HSE_TargetItem:
        break;
    case EHuntSkillEnum::HSE_Specific:
        break;
    default:
        break;
    }
}

void AAssassinCharacter::SetStab( bool IsStab )
{
    bIsStab = IsStab;

    // If this next check succeeds, we are *not* the authority, meaning we are a network client.
    // In this case we also want to call the server function to tell it to change the bSomeBool property as well.
    if ( Role < ROLE_Authority )
    {
        ServerSetStab( IsStab );
    }
}

void AAssassinCharacter::ServerSetStab_Implementation( bool IsStab )
{
    // This function is only called on the server (where Role == ROLE_Authority), called over the network by clients.
    // We need to call SetSomeBool() to actually change the value of the bool now!
    // Inside that function, Role == ROLE_Authority, so it won't try to call ServerSetSomeBool() again.
    SetStab( IsStab );
}

bool AAssassinCharacter::ServerSetStab_Validate( bool IsStab )
{
    return true;
}

void AAssassinCharacter::SetCurrentHuntSkill( EHuntSkillEnum Skill )
{
    CurrentHuntSkill = Skill;

    if ( Role < ROLE_Authority )
    {
        ServerSetCurrentHuntSkill( Skill );
    }
}

void AAssassinCharacter::ServerSetCurrentHuntSkill_Implementation( EHuntSkillEnum Skill )
{
    SetCurrentHuntSkill( CurrentHuntSkill );
}

bool AAssassinCharacter::ServerSetCurrentHuntSkill_Validate( EHuntSkillEnum Skill )
{
    return true;
}

void AAssassinCharacter::SwitchConcealedItem()
{
    SetCurrentHuntSkill( EHuntSkillEnum::HSE_ConcealedItem );
}

void AAssassinCharacter::SwitchTargetItem()
{
    SetCurrentHuntSkill( EHuntSkillEnum::HSE_TargetItem );
}
