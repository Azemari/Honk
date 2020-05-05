// Fill out your copyright notice in the Description page of Project Settings.

#include "HonkGameMode.h"
#include "HonkPawn.h"
#include "HonkHud.h"

AHonkGameMode::AHonkGameMode()
{
    DefaultPawnClass = AHonkPawn::StaticClass();
    HUDClass = AHonkHud::StaticClass();
}
