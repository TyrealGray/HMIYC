// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "AssassinCharacter.h"
#include "UnrealNetwork.h"

AAssassinCharacter::AAssassinCharacter():
    bIsStab( false )
{
}

void AAssassinCharacter::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentHuntSkill( EHuntSkillEnum::HSE_ConcealedItem );

    InitDagger();
}

void AAssassinCharacter::InitDagger()
{
    TSubclassOf<AActor> DaggerActor = StaticLoadClass( AActor::StaticClass(),
                                      nullptr, TEXT( "/Game/Blueprints/Equipments/Dagger/BP_NormalDaggerActor.BP_NormalDaggerActor_C" ) );

    FActorSpawnParameters SpawnParameter;

    SpawnParameter.Owner = this;

    ConcealedItemActor = GetWorld()->SpawnActor<AActor>( ( nullptr == DaggerActor ) ? AActor::StaticClass() : DaggerActor, SpawnParameter );

    ConcealedItemActor->SetActorHiddenInGame( true );

    ConcealedItemActor->AttachRootComponentTo( GetMesh(), FName( "ConcealedItem" ), EAttachLocation::SnapToTarget, false );
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
    InputComponent->BindAction( "Unique", IE_Pressed, this, &AAssassinCharacter::SwitchUnique );
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
    if ( IsDead() )
    {
        return;
    }

    switch ( CurrentHuntSkill )
    {
    case EHuntSkillEnum::HSE_ConcealedItem:
        UseConcealedItem();
        break;
    case EHuntSkillEnum::HSE_TargetItem:
        UseTargetItem();
        break;
    case EHuntSkillEnum::HSE_Unique:
        UseUnique();
        break;
    default:
        break;
    }
}

void AAssassinCharacter::UseConcealedItem()
{
    if ( Role < ROLE_Authority )
    {
        ServerUseConcealedItem();
    }

    SetStabBegin();

    SetActorRotation( FRotator( 0.0f, Controller->GetControlRotation().Yaw, 0.0f ) );

    FCollisionQueryParams TraceParams = FCollisionQueryParams( FName( TEXT( "Trace" ) ), false, this );

    FHitResult Result;

    GetWorld()->LineTraceSingleByChannel( Result, GetActorLocation(),
                                          GetActorLocation() + GetViewRotation().RotateVector( FVector( 100.0f, 0.0f, 0.0f ) ), ECC_Pawn, TraceParams );

    AActor* Actor = Result.GetActor();

    if ( !Result.bBlockingHit || !Actor->IsA( ANormalCharacter::StaticClass() ) )
    {
        return;
    }

    if ( !Cast<ANormalCharacter>( Actor )->OnPlayerHit() )
    {
        GoIntoStatus( EStatusEnum::SE_Expose );
    }
}

void AAssassinCharacter::ServerUseConcealedItem_Implementation()
{
    UseConcealedItem();
}

bool AAssassinCharacter::ServerUseConcealedItem_Validate()
{
    return true;
}

void AAssassinCharacter::UseTargetItem()
{
}

void AAssassinCharacter::UseUnique()
{
}

void AAssassinCharacter::GoIntoStatus( EStatusEnum NewStatus )
{
    switch ( NewStatus )
    {
    case  EStatusEnum::SE_Expose:
        BeExpose();
        break;
    default:
        break;
    }

    SetCurrentStatus( NewStatus );
}

void AAssassinCharacter::SetStabBegin()
{
    SetStab( true );

    GetWorldTimerManager().ClearTimer( StabTimer );
    GetWorldTimerManager().SetTimer( StabTimer, this, &AAssassinCharacter::SetStabOver, 0.3f, true );

    ConcealedItemActor->SetActorHiddenInGame( false );
}

void AAssassinCharacter::SetStabOver()
{
    SetStab( false );

    ConcealedItemActor->SetActorHiddenInGame( true );
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
    ConcealedItemActor->SetActorHiddenInGame( !IsStab );
}

bool AAssassinCharacter::ServerSetStab_Validate( bool IsStab )
{
    return true;
}

void AAssassinCharacter::SetCurrentStatus( EStatusEnum Status )
{
    CurrentStatus = Status;

    if ( Role < ROLE_Authority )
    {
        ServerSetCurrentStatus( Status );
    }
}

void AAssassinCharacter::ServerSetCurrentStatus_Implementation( EStatusEnum Status )
{
    SetCurrentStatus( Status );
}

bool AAssassinCharacter::ServerSetCurrentStatus_Validate( EStatusEnum Status )
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

void AAssassinCharacter::SetCurrentRunningSkill( ERunningSkillEnum Skill )
{
    CurrentRunningSkill = Skill;

    if ( Role < ROLE_Authority )
    {
        ServerSetCurrentRunningSkill( Skill );
    }
}

void AAssassinCharacter::ServerSetCurrentRunningSkill_Implementation( ERunningSkillEnum Skill )
{
    SetCurrentRunningSkill( Skill );
}

bool AAssassinCharacter::ServerSetCurrentRunningSkill_Validate( ERunningSkillEnum Skill )
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

void AAssassinCharacter::SwitchUnique()
{
    SetCurrentHuntSkill( EHuntSkillEnum::HSE_Unique );
}

void AAssassinCharacter::Exposed()
{
}

void AAssassinCharacter::BeExpose_Implementation()
{
    Exposed();
}

bool AAssassinCharacter::OnPlayerHit()
{
    ANormalCharacter::OnPlayerHit();
    return true;
}
