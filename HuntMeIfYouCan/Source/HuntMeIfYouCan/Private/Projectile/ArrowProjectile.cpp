// GPLv2

#include "HuntMeIfYouCan.h"

#include "ArrowProjectile.h"
#include "UnrealNetwork.h"
#include "AssassinCharacter.h"


// Sets default values
AArrowProjectile::AArrowProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Use a sphere as a simple collision representation
    CollisionComp = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereComp" ) );
    CollisionComp->InitSphereRadius( 5.0f );
    CollisionComp->OnComponentHit.AddDynamic( this, &AArrowProjectile::OnHit );		// set up a notification for when this component hits something blocking

    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride( FWalkableSlopeOverride( WalkableSlope_Unwalkable, 0.f ) );
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Set as root component
    RootComponent = CollisionComp;

    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileComp" ) );
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    // Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AArrowProjectile::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AArrowProjectile::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

void AArrowProjectile::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    Super::GetLifetimeReplicatedProps( OutLifetimeProps );

    DOREPLIFETIME( AArrowProjectile, ArrowOwner );
}

void AArrowProjectile::SetArrowOwner( class AAssassinCharacter *Assassin )
{
    if ( Role < ROLE_Authority )
    {
        ServerSetArrowOwner( Assassin );
    }

    ArrowOwner = Assassin;
}

void AArrowProjectile::ServerSetArrowOwner_Implementation( class AAssassinCharacter *Assassin )
{
    SetArrowOwner( Assassin );
}

bool AArrowProjectile::ServerSetArrowOwner_Validate( class AAssassinCharacter *Assassin )
{
    return ( Role >= ROLE_Authority );
}

void AArrowProjectile::OnHit( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
    if ( ( OtherActor != NULL ) && ( OtherActor != this ) && ( OtherComp != NULL ) )
    {
        auto Civilian = Cast<ANormalCharacter>( OtherActor );

        if ( NULL != Civilian && !Civilian->OnPlayerHit( ArrowOwner ) )
        {
            ArrowOwner->GoIntoStatus( EStatusEnum::SE_Expose );
        }

        Destroy();
    }
}

