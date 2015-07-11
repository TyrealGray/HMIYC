// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "HMIYCGameInstance.generated.h"

/**
 *
 */
UCLASS()
class HUNTMEIFYOUCAN_API UHMIYCGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:

    UHMIYCGameInstance(const FObjectInitializer &objectInitializer);

    UFUNCTION(BlueprintCallable, category = "OpenUI")
    void openMainMenu();

    UFUNCTION(BlueprintCallable, category = "OpenUI")
    void openServerList();

    UFUNCTION(BlueprintCallable, category = "OpenUI")
    void openPauseMenu();

private:
    UPROPERTY()
    UUserWidget* MainMenu;
    UPROPERTY()
    UUserWidget* ServerList;
    UPROPERTY()
    UUserWidget* PauseMenu;

    class UUserWidget* CreateUIWidget(const FString& Path);
};
