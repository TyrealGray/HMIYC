// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "AssassinCharacter.h"
#include "UnrealNetwork.h"
#include "SpawnerFunctionLibrary.h"
#include "../HMIYCPlayerState.h"
#include "../HMIYCGameInstance.h"

AAssassinCharacter::AAssassinCharacter():
    bIsStab( false ),
    bIsHoldBow( false ),
    CurrentStatus( EStatusEnum::SE_Masquerade ),
    bIsTargetItemColdDown( false ),
    ExposeBGMAudio( nullptr )
{
    BowOffset = FVector( 100.0f, 0.0f, 10.0f );
}

void AAssassinCharacter::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentHuntSkill( EHuntSkillEnum::HSE_ConcealedItem );

    InitDagger();

    InitBow();
}

void AAssassinCharacter::InitDagger()
{
    FActorSpawnParameters SpawnParameter;

    SpawnParameter.Owner = this;

    ConcealedItemActor = GetWorld()->SpawnActor<AActor>( ( nullptr == DaggerActorClass ) ? AActor::StaticClass() : DaggerActorClass,
                         SpawnParameter );

    ConcealedItemActor->SetActorHiddenInGame( true );

    ConcealedItemActor->AttachRootComponentTo( GetMesh(), FName( "ConcealedItem" ),
            EAttachLocation::SnapToTarget, false );
}


void AAssassinCharacter::InitBow()
{
    FActorSpawnParameters SpawnParameter;

    SpawnParameter.Owner = this;

    TargetItemActor = GetWorld()->SpawnActor<AActor>( ( nullptr == BowActorClass ) ? AActor::StaticClass() : BowActorClass,
                      SpawnParameter );

    TargetItemActor->SetActorHiddenInGame( true );

    TargetItemActor->AttachRootComponentTo( GetMesh(), FName( "TargetItem" ), EAttachLocation::KeepRelativeOffset, false );
}

void AAssassinCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

void AAssassinCharacter::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
    Super::SetupPlayerInputComponent( InputComponent );

    InputComponent->BindAction( "Jump", IE_Pressed, this, &AAssassinCharacter::JumpPrepared );
    InputComponent->BindAction( "Jump", IE_Released, this, &AAssassinCharacter::JumpDeliver );

    InputComponent->BindAction( "UseSkill", IE_Pressed, this, &AAssassinCharacter::UseSkill );
    InputComponent->BindAction( "UseSkill", IE_Released, this, &AAssassinCharacter::UseSkillConfirmed );

    InputComponent->BindAction( "ConcealedItem", IE_Pressed, this, &AAssassinCharacter::SwitchConcealedItem );
    InputComponent->BindAction( "TargetItem", IE_Pressed, this, &AAssassinCharacter::SwitchTargetItem );
    InputComponent->BindAction( "Unique", IE_Pressed, this, &AAssassinCharacter::SwitchUnique );
}

void AAssassinCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps( OutLifetimeProps );

    DOREPLIFETIME( AAssassinCharacter, bIsStab );
    DOREPLIFETIME( AAssassinCharacter, bIsHoldBow );
    DOREPLIFETIME( AAssassinCharacter, CurrentStatus );
    DOREPLIFETIME( AAssassinCharacter, CurrentHuntSkill );
    DOREPLIFETIME( AAssassinCharacter, CurrentRunningSkill );
}

void AAssassinCharacter::UseSkill()
{
    if ( EStatusEnum::SE_Dead == CurrentStatus || EStatusEnum::SE_Expose == CurrentStatus )
    {
        GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, "Your status can't do it right now" );
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

void AAssassinCharacter::UseSkillConfirmed()
{
    if ( EStatusEnum::SE_Dead == CurrentStatus || EStatusEnum::SE_Expose == CurrentStatus )
    {
        ItemHide();
        GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, "Your status can't do it right now" );
        return;
    }

    switch ( CurrentHuntSkill )
    {
    case EHuntSkillEnum::HSE_ConcealedItem:
        UseConcealedItemConfirmed();
        break;
    case EHuntSkillEnum::HSE_TargetItem:
        UseTargetItemConfirmed();
        break;
    case EHuntSkillEnum::HSE_Unique:
        break;
    default:
        break;
    }

    ItemHide();
}

void AAssassinCharacter::UseConcealedItem()
{
    if ( Role < ROLE_Authority )
    {
        ServerUseConcealedItem();
    }

    SetStab( true );
    ConcealedItemActor->SetActorHiddenInGame( false );

    SetActorRotation( FRotator( 0.0f, Controller->GetControlRotation().Yaw, 0.0f ) );

    if ( NULL != FireConcealedItemSound )
    {
        UGameplayStatics::PlaySoundAtLocation( this, FireConcealedItemSound, GetActorLocation() );
    }

    FCollisionQueryParams TraceParams = FCollisionQueryParams( FName( TEXT( "Trace" ) ), false, this );

    FHitResult Result;

    GetWorld()->LineTraceSingleByChannel( Result, GetActorLocation(),
                                          GetActorLocation() + GetViewRotation().RotateVector( FVector( 100.0f, 0.0f, 0.0f ) ),
                                          ECC_Pawn, TraceParams );

    AActor* Actor = Result.GetActor();

    if ( !Result.bBlockingHit || !Actor->IsA( ANormalCharacter::StaticClass() ) )
    {
        return;
    }

    if ( !Cast<ANormalCharacter>( Actor )->OnPlayerHit( this ) )
    {
        GoIntoStatus( EStatusEnum::SE_Expose );

        if ( nullptr != ExposeBGMAudio )
        {
            ExposeBGMAudio->Stop();
        }

        ExposeBGMAudio = UGameplayStatics::SpawnSound2D( this, LoadObject<USoundWave>( nullptr, TEXT( "/Game/Audio/BGM/Escape_from_East_Berlin_clip.Escape_from_East_Berlin_clip" ) ) );

    }

}

void AAssassinCharacter::ServerUseConcealedItem_Implementation()
{
    UseConcealedItem();
}

bool AAssassinCharacter::ServerUseConcealedItem_Validate()
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::UseConcealedItemConfirmed()
{
    if ( Role < ROLE_Authority )
    {
        ServerUseConcealedItemConfirmed();
    }
}

void AAssassinCharacter::ServerUseConcealedItemConfirmed_Implementation()
{
    UseConcealedItemConfirmed();
}

bool AAssassinCharacter::ServerUseConcealedItemConfirmed_Validate()
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::UseTargetItem()
{
    if ( Role < ROLE_Authority )
    {
        ServerUseTargetItem();
    }

    if ( bIsTargetItemColdDown )
    {
        GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Red, "Your TargetItem ColdDown right now" );
        return;
    }

    SetIsHoldBow( true );

    TargetItemActor->SetActorHiddenInGame( false );
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
    case EStatusEnum::SE_Crawling:
        BeCrawling();
        break;
    case EStatusEnum::SE_Dead:
        BeDying();
    default:
        break;
    }

    SetCurrentStatus( NewStatus );
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

void AAssassinCharacter::TargetItemColdDown()
{
    bIsTargetItemColdDown = true;
}

void AAssassinCharacter::TargetItemReady()
{
    bIsTargetItemColdDown = false;
}

void AAssassinCharacter::ItemHide()
{

    if ( Role < ROLE_Authority )
    {
        ServerItemHide();
    }

    SetStab( false );
    ConcealedItemActor->SetActorHiddenInGame( true );

    SetIsHoldBow( false );
    TargetItemActor->SetActorHiddenInGame( true );
}

void AAssassinCharacter::ServerItemHide_Implementation()
{
    ItemHide();
}

bool AAssassinCharacter::ServerItemHide_Validate()
{
    return ( Role >= ROLE_Authority );
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
    ServerSetCurrentStatus( Status );
}

void AAssassinCharacter::ServerSetCurrentStatus_Implementation( EStatusEnum Status )
{
    CurrentStatus = Status;
}

bool AAssassinCharacter::ServerSetCurrentStatus_Validate( EStatusEnum Status )
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::SetCurrentHuntSkill( EHuntSkillEnum Skill )
{
    ServerSetCurrentHuntSkill( Skill );
}

void AAssassinCharacter::ServerSetCurrentHuntSkill_Implementation( EHuntSkillEnum Skill )
{
    CurrentHuntSkill = Skill;
}

bool AAssassinCharacter::ServerSetCurrentHuntSkill_Validate( EHuntSkillEnum Skill )
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::SetCurrentRunningSkill( ERunningSkillEnum Skill )
{
    ServerSetCurrentRunningSkill( Skill );
}

void AAssassinCharacter::ServerSetCurrentRunningSkill_Implementation( ERunningSkillEnum Skill )
{
    CurrentRunningSkill = Skill;
}

bool AAssassinCharacter::ServerSetCurrentRunningSkill_Validate( ERunningSkillEnum Skill )
{
    return ( Role >= ROLE_Authority );
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
    auto MeshMaterialInstances = GetMeshMaterialInstances();

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Head]->SetTextureParameterValue(
        FName( "ManHeadTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Head ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Hand]->SetTextureParameterValue(
        FName( "ManHandTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Hand ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Foot]->SetTextureParameterValue(
        FName( "ManFootTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Foot ) );

    MeshMaterialInstances[EMaterialInstanceIDEnum::MII_Body]->SetTextureParameterValue(
        FName( "ManBodyTextureParameter" ), GetMeshTexture( EMaterialInstanceIDEnum::MII_Body ) );

    GetWorldTimerManager().ClearTimer( ExposeTimer );
    GetWorldTimerManager().SetTimer( ExposeTimer, this, &AAssassinCharacter::GoCrawling, 30.0f, false );
}

void AAssassinCharacter::BeExpose_Implementation()
{
    Exposed();
}

void AAssassinCharacter::BeDying()
{
    GetWorldTimerManager().ClearTimer( DyingTimer );
    GetWorldTimerManager().SetTimer( DyingTimer, this, &AAssassinCharacter::GoDead, 3.0f, false );
}

void AAssassinCharacter::BeCrawling()
{
    GetWorldTimerManager().ClearTimer( CrawlingTimer );
    GetWorldTimerManager().SetTimer( CrawlingTimer, this, &AAssassinCharacter::GoMasquerade, 5.0f, false );

    GEngine->AddOnScreenDebugMessage( -1, 3.0, FColor::Yellow, TEXT( "BeCrawling" ) );
}

void AAssassinCharacter::GoCrawling()
{
    if ( EStatusEnum::SE_Dead == CurrentStatus )
    {
        return;
    }

    GoIntoStatus( EStatusEnum::SE_Crawling );

    SetActorHiddenInGame( true );
}

bool AAssassinCharacter::OnPlayerHit( class AAssassinCharacter *Assassin /*= nullptr*/ )
{
    if ( EStatusEnum::SE_Crawling == CurrentStatus )
    {
        return true;
    }

    if ( nullptr != Assassin )
    {
        Assassin->BeScoring( Assassin->PlayerState->Score + 1 );
    }

    ANormalCharacter::OnPlayerHit();
    GoIntoStatus( EStatusEnum::SE_Dead );
    return true;
}

void AAssassinCharacter::JumpPrepared()
{
    if ( EStatusEnum::SE_Dead == CurrentStatus )
    {
        return;
    }
    Jump();
}

void AAssassinCharacter::JumpDeliver()
{
    StopJumping();
}

UTexture2D * AAssassinCharacter::GetMeshTexture( int32 ID )
{
    UTexture2D* Texture = nullptr;
    switch ( ID )
    {
    case EMaterialInstanceIDEnum::MII_Head:
        Texture = HeadMeshTexture;
        break;
    case	EMaterialInstanceIDEnum::MII_Hand:
        Texture = HandMeshTexture;
        break;
    case	EMaterialInstanceIDEnum::MII_Foot:
        Texture = FootMeshTexture;
        break;
    case	EMaterialInstanceIDEnum::MII_Body:
        Texture = BodyMeshTexture;
        break;
    default:
        break;
    }
    return Texture;
}

void AAssassinCharacter::GoMasquerade()
{
    RandomMeshTexture();

    SetActorHiddenInGame( false );

    SetCurrentStatus( EStatusEnum::SE_Masquerade );
}

void AAssassinCharacter::BeScoring_Implementation( float Score )
{
    PlayerState->Score = Score;

    if ( 5 > PlayerState->Score )
    {
        return;
    }

    Cast<UHMIYCGameInstance>( GetGameInstance() )->GameWinnerShowed();
}

void AAssassinCharacter::SetIsHoldBow( bool IsHoldBow )
{
    ServerSetIsHoldBow( IsHoldBow );
}

void AAssassinCharacter::ServerSetIsHoldBow_Implementation( bool IsHoldBow )
{
    bIsHoldBow = IsHoldBow;
}

bool AAssassinCharacter::ServerSetIsHoldBow_Validate( bool IsHoldBow )
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::ServerUseTargetItem_Implementation()
{
    UseTargetItem();
}

bool AAssassinCharacter::ServerUseTargetItem_Validate()
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::UseTargetItemConfirmed()
{
    if ( Role < ROLE_Authority )
    {
        ServerUseTargetItemConfirmed();
    }

    if ( !bIsHoldBow || bIsTargetItemColdDown )
    {
        return;
    }

    if ( NULL != FireTargetItemSound )
    {
        UGameplayStatics::PlaySoundAtLocation( this, FireTargetItemSound, GetActorLocation() );
    }

    SetActorRotation( FRotator( 0.0f, Controller->GetControlRotation().Yaw, 0.0f ) );

    if ( ArrowProjectileClass != NULL )
    {
        const FRotator SpawnRotation = GetControlRotation();
        // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
        const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector( BowOffset );

        UWorld* const World = GetWorld();
        if ( World != NULL )
        {
            // spawn the projectile at the muzzle
            auto arrow = World->SpawnActor<AArrowProjectile>( ArrowProjectileClass, SpawnLocation, SpawnRotation );
            arrow->SetArrowOwner( this );
        }
    }

    TargetItemColdDown();

    GetWorldTimerManager().ClearTimer( TargetItemColdDownTimer );
    GetWorldTimerManager().SetTimer( TargetItemColdDownTimer, this, &AAssassinCharacter::TargetItemReady, 5.0f, false );
}

void AAssassinCharacter::ServerUseTargetItemConfirmed_Implementation()
{
    UseTargetItemConfirmed();
}

bool AAssassinCharacter::ServerUseTargetItemConfirmed_Validate()
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::ServerBeDying_Implementation( AController* PlayerController )
{
    GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::Blue, "Now SomeOne Were dead!" );

    FVector RandomLoaction = USpawnerFunctionLibrary::GetRandomLoactionAtSpawnZone();

    FRotator RandomRotation = FRotator( 0.0f, FMath::FRandRange( 0.0f, 360.0f ), 0.0f );

    FActorSpawnParameters SpawnParameter;

    SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* OldPawn = PlayerController->GetPawn();

    PlayerController->UnPossess();

    OldPawn->Destroy();

    AActor* NewCharacter = GetWorld()->SpawnActor( USpawnerFunctionLibrary::GetRandomAssassinCharacterClass(),
                           &RandomLoaction, &RandomRotation, SpawnParameter );

    PlayerController->Possess( Cast<APawn>( NewCharacter ) );
}

bool AAssassinCharacter::ServerBeDying_Validate( AController* PlayerController )
{
    return ( Role >= ROLE_Authority );
}

void AAssassinCharacter::GoDead()
{
    ServerBeDying( Controller );
}
