// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "CivilianSpawner.h"


// Sets default values
ACivilianSpawner::ACivilianSpawner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SetReplicates(true);

    SetActorHiddenInGame(true);

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));

    SpawnArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    SpawnArea->AttachTo(Root);

    RootComponent = Root;
}

// Called when the game starts or when spawned
void ACivilianSpawner::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ACivilianSpawner::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

