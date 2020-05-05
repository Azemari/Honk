// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HonkHud.generated.h"

UCLASS(config = Game)
class HONK_API AHonkHud : public AHUD
{
	GENERATED_BODY()
public:
    AHonkHud();

    /** Font used to render the vehicle info */
    UPROPERTY()
    UFont* HUDFont;

    // Begin AHUD interface
    virtual void DrawHUD() override;
    // End AHUD interface
};
