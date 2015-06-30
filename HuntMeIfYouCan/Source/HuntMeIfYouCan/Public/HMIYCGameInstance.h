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
    UUserWidget* m_pMainMenu;
    UPROPERTY()
    UUserWidget* m_pServerList;
    UPROPERTY()
    UUserWidget* m_pPauseMenu;

    void createUIWidget(UUserWidget* &pWidget, const FString& strPath);
};
