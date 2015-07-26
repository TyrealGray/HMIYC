// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "ArcherCharacter.h"

AArcherCharacter::AArcherCharacter()
{

}

void AArcherCharacter::UseConcealedItem()
{
    SetStab( true );

    FHitResult Result;

    UGameplayStatics::GetPlayerController( GetWorld(), 0 )->GetHitResultUnderCursorByChannel( UEngineTypes::ConvertToTraceType( ECC_Pawn ), false, Result );

    AActor* Actor = Result.GetActor();

    if ( !Result.bBlockingHit || nullptr == Cast<ANormalCharacter>( Actor ) || 2000 < FVector::Dist( Actor->GetActorLocation(), GetActorLocation() ) )
    {
        return;
    }

    GEngine->AddOnScreenDebugMessage( -1, 3.0, FColor::Red, TEXT( "“ôÖÐ!" + Result.GetActor()->GetName() ) );
}
