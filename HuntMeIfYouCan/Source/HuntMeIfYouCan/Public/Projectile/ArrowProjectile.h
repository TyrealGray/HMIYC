// GPLv2

#pragma once

#include "GameFramework/Actor.h"
#include "ArrowProjectile.generated.h"

UCLASS()
class HUNTMEIFYOUCAN_API AArrowProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AArrowProjectile();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    void SetArrowOwner( class AAssassinCharacter *Assassin );

    UFUNCTION()
    void OnHit( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

private:
    UPROPERTY( VisibleDefaultsOnly, Category = Projectile )
    class USphereComponent * CollisionComp;

    /** Projectile movement component */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = ( AllowPrivateAccess = "true" ) )
    class UProjectileMovementComponent * ProjectileMovement;

    class AAssassinCharacter *ArrowOwner;

};
