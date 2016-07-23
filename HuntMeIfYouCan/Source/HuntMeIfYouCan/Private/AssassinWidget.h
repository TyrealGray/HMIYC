// GPLv2

#pragma once

#include "Blueprint/UserWidget.h"
#include "AssassinWidget.generated.h"

/**
 *
 */
UCLASS()
class UAssassinWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintImplementableEvent, category = "CommonUIEvent" )
    void CantUseSkillTextShowed();

    UFUNCTION( BlueprintImplementableEvent, category = "CommonUIEvent" )
    void ExposedBackgroundShowed();

    UFUNCTION( BlueprintImplementableEvent, category = "CommonUIEvent" )
    void TargetItemColdDown();
};
