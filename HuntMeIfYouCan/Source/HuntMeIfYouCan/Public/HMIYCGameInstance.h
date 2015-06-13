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

private:
    UUserWidget* m_pMainMenu;
    UUserWidget* m_pServerList;

    void createUIWidget(UUserWidget* &pWidget, const FString& strPath);
};
