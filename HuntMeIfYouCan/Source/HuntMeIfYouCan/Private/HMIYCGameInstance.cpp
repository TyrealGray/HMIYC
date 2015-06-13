// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "HMIYCGameInstance.h"

const int32 UI_ZORDER = 10;
UHMIYCGameInstance::UHMIYCGameInstance(const FObjectInitializer &objectInitializer):
    Super(objectInitializer),
    m_pMainMenu(NULL),
    m_pServerList(NULL)
{

}

void UHMIYCGameInstance::openMainMenu()
{
    if (NULL == m_pMainMenu)
    {
        createUIWidget(m_pMainMenu, "/Game/Blueprints/Widgets/MainMenu.MainMenu_C");
    }

    if (NULL != m_pServerList && m_pServerList->IsVisible())
    {
        m_pServerList->SetVisibility(ESlateVisibility::Hidden);
    }

    m_pMainMenu->SetVisibility(ESlateVisibility::Visible);
}

void UHMIYCGameInstance::openServerList()
{
    if (NULL == m_pServerList)
    {
        createUIWidget(m_pServerList, "/Game/Blueprints/Widgets/ServerList.ServerList_C");
    }

    if (NULL != m_pMainMenu && m_pMainMenu->IsVisible())
    {
        m_pMainMenu->SetVisibility(ESlateVisibility::Hidden);
    }
    m_pServerList->SetVisibility(ESlateVisibility::Visible);
}

void UHMIYCGameInstance::createUIWidget(UUserWidget* &pWidget, const FString& strPath)
{
    UClass* pWidgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, *strPath);

    pWidget = CreateWidget<UUserWidget>(GetWorld(), pWidgetClass);

    pWidget->AddToViewport(UI_ZORDER);

    pWidget->SetVisibility(ESlateVisibility::Hidden);
}
