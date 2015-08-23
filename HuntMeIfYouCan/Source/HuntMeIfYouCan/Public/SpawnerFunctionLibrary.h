// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawnerFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class HUNTMEIFYOUCAN_API USpawnerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable, category = SpawnerLibrary )
    static void InitSpawnerManager( TArray<class ACivilianSpawner*> SpawnerArray );

    UFUNCTION( BlueprintCallable, category = SpawnerLibrary )
    static void CivilianRespawn();

    UFUNCTION( BlueprintCallable, category = SpawnLibrary )
    static TSubclassOf<class AActor>  GetRandomAssassinCharacterClass();

private:
    static FString GetRandomAssassinBlueprintPath();
};
