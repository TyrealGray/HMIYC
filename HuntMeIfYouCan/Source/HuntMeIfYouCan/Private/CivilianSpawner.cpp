// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "CivilianSpawner.h"
#include "NormalCharacter.h"

const int32 NUMBER_OF_CIVILIAN_TYPE = 1;
// Sets default values
ACivilianSpawner::ACivilianSpawner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SetReplicates ( true );

    SetActorHiddenInGame ( true );

    RootComponent = Root;

    Root = CreateDefaultSubobject<USceneComponent> ( TEXT ( "Root" ) );

    SpawnArea = CreateDefaultSubobject<UBoxComponent>( TEXT( "SpawnArea" ) );

    SpawnArea->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );

    SpawnArea->AttachTo ( Root );
}

// Called when the game starts or when spawned
void ACivilianSpawner::BeginPlay()
{
    Super::BeginPlay();

    Init();
}

void ACivilianSpawner::Init()
{
    if ( IsInit() )
    {
        return;
    }

    SpawnBox = FBox ( -SpawnArea->GetScaledBoxExtent(), SpawnArea->GetScaledBoxExtent() );

    bIsInit = true;
}

// Called every frame
void ACivilianSpawner::Tick ( float DeltaTime )
{
    Super::Tick ( DeltaTime );
}

void ACivilianSpawner::SpawnCivilian()
{
    FVector RandomPoint = GetRandomLocation();

    FRotator RandomRotation = FRotator ( 0.0f, FMath::FRandRange ( 0.0f, 360.0f ), 0.0f );

    FActorSpawnParameters SpawnParameter;

    SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ANormalCharacter* Civilian = Cast<ANormalCharacter> ( GetWorld()->SpawnActor ( CivilianClass, &RandomPoint, &RandomRotation, SpawnParameter ) );

    if ( nullptr == Civilian )
    {
        GEngine->AddOnScreenDebugMessage ( -1, 3.0, FColor::Red, TEXT ( "村民無法生成SpawnCivilian is Null" ) );
        return;
    }

    Civilian->SpawnDefaultController();

    Civilian->SetIsNPC ( true );

    GEngine->AddOnScreenDebugMessage ( -1, 3.0, FColor::White, TEXT ( "村民生成SpawnCivilian X: " ) + FString::SanitizeFloat ( RandomPoint.X ) + " Y: " + FString::SanitizeFloat ( RandomPoint.Y ) + " Z: " + FString::SanitizeFloat ( RandomPoint.Z ) );
}

bool ACivilianSpawner::IsInit()
{
    return bIsInit;
}

FVector ACivilianSpawner::GetRandomLocation()
{
    FVector RandomLocation = GetActorLocation() + FMath::RandPointInBox ( SpawnBox );

    RandomLocation.Z += 60.0f;

    return RandomLocation;
}