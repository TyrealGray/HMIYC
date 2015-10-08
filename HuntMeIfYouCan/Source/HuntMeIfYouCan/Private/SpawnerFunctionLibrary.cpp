// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "SpawnerFunctionLibrary.h"
#include "CivilianSpawnerManager.h"
#include "CivilianSpawner.h"
#include "AssassinCharacter.h"
#include "AssassinsNameList.h"

void USpawnerFunctionLibrary::InitSpawnerManager( TArray<class ACivilianSpawner*> SpawnerArray )
{
    CivilianSpawnerManager* ManagerInstance = CivilianSpawnerManager::GetInstance();
    ManagerInstance->SetCivilianSpawners( SpawnerArray );

    int32 NumberOfCivilians = ManagerInstance->GetNumberOfCivilianNeed();

    for ( int32 Index = 0; Index < NumberOfCivilians; ++Index )
    {
        ManagerInstance->CivilianRespawn();
    }

}

void USpawnerFunctionLibrary::CivilianRespawn()
{
    CivilianSpawnerManager::GetInstance()->CivilianRespawn();
}

TSubclassOf<class AActor>  USpawnerFunctionLibrary::GetRandomAssassinCharacterClass()
{
    FString AssassinBlueprintPath = GetRandomAssassinBlueprintPath();

    return StaticLoadClass( AAssassinCharacter::StaticClass(), nullptr, *AssassinBlueprintPath );
}

FString USpawnerFunctionLibrary::GetRandomAssassinBlueprintPath()
{
    AssassinsNameList* NameListInstance = AssassinsNameList::GetInstance();

    int32 SelectedNumber = FMath::FRandRange( 0, NameListInstance->GetNumberOfAssassinsType() );

    FString AssassinName = NameListInstance->GetNameByID( SelectedNumber );

    return "/Game/Blueprints/Characters/Assassin/" + AssassinName + "." + AssassinName + "_C";
}
