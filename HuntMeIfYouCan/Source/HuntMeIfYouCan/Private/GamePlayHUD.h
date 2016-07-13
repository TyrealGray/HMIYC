// GPLv2

#pragma once

#include "GameFramework/HUD.h"
#include "GamePlayHUD.generated.h"

/**
 *
 */
UCLASS()
class AGamePlayHUD : public AHUD
{
    GENERATED_BODY()

public:

    AGamePlayHUD();

    /** Primary draw call for the HUD */
    virtual void DrawHUD() override;

private:
    /** Crosshair asset pointer */
    class UTexture2D* CrosshairTex;


};
