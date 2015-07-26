// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "ArcherCharacter.h"

AArcherCharacter::AArcherCharacter()
{

}

void AArcherCharacter::UseConcealedItem()
{
    SetStab( true );

    FCollisionQueryParams TraceParams = FCollisionQueryParams( FName( TEXT( "Trace" ) ), false, this );

    FHitResult Result;

    GetWorld()->LineTraceSingleByChannel( Result, GetActorLocation(),
                                          GetActorLocation() + GetViewRotation().RotateVector( FVector( 100.0f, 0.0f, 0.0f ) ), ECC_Pawn, TraceParams );

    AActor* Actor = Result.GetActor();

    if ( !Result.bBlockingHit ||  !Actor->IsA( ANormalCharacter::StaticClass() ) || 2000 < FVector::Dist( Actor->GetActorLocation(), GetActorLocation() ) )
    {
        return;
    }

    GEngine->AddOnScreenDebugMessage( -1, 3.0, FColor::Red, TEXT( "“ôÖÐ!Stab on: " + Actor->GetName() ) );
}
