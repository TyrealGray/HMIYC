// GPLv2

#include "HuntMeIfYouCan.h"
#include "ArrowProjectile.h"


// Sets default values
AArrowProjectile::AArrowProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

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

void AArrowProjectile::OnHit( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{

}

