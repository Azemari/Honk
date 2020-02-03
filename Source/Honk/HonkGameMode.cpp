// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonkGameMode.h"
#include "HonkPawn.h"
#include "HonkHud.h"

AHonkGameMode::AHonkGameMode()
{
	DefaultPawnClass = AHonkPawn::StaticClass();
	HUDClass = AHonkHud::StaticClass();
}
