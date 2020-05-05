// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkHud.h"
#include "Engine/Font.h"
#include "ConstructorHelpers.h"

AHonkHud::AHonkHud()
{
    static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void AHonkHud::DrawHUD()
{
    Super::DrawHUD();
}
