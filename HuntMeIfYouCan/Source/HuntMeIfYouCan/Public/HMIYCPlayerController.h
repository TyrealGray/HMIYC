// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HMIYCPlayerController.generated.h"

/**
 *
 */
UCLASS()
class HUNTMEIFYOUCAN_API AHMIYCPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AHMIYCPlayerController( const FObjectInitializer& objectInitializer );

    virtual void SetupInputComponent() override;

    virtual void BeginPlay() override;

    UFUNCTION( BlueprintCallable, category = "StartGame" )
    void StartGameNow();

    UFUNCTION( BlueprintCallable, category = "GameUI" )
    void SetCharacterUI( const FString& Path );

    void InitCommonUI();

    void ShowExposeUIBG();

    void ShowCantUseSkillText();

    void ShowTargetItemColdDown();

private:

    UPROPERTY()
    class UAssassinWidget * CharacterMenu;

    UPROPERTY()
    class UAssassinWidget * CommonCharacterMenu;

    void OnMoveForward( float Value );
    void OnMoveRight( float Value );

    void OnTurn( float Value );
    void OnLookUp( float Value );

    class UAssassinWidget* GetAssassinWidget( const FString& Path, int32 ZOrder );

};
