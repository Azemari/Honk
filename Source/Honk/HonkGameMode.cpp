// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonkGameMode.h"
#include "HonkPawn.h"
#include "Engine/World.h"
#include "HonkPlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "HonkHud.h"

AHonkGameMode::AHonkGameMode()
{
	
	DefaultPawnClass = AHonkPawn::StaticClass();
	HUDClass = AHonkHud::StaticClass();
}

void AHonkGameMode::BeginPlay()
{ 	
	Super::BeginPlay();
}

AActor* AHonkGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* EmergencyBackup = nullptr;
	if (APlayerController* PlayerCont = Cast<APlayerController>(Player))
	{
		for (TActorIterator<AHonkPlayerStart> StartIt(GetWorld()); StartIt; ++StartIt)
		{
			if (*StartIt)
			{
				EmergencyBackup = *StartIt;
				if (StartIt->PlayerNum == PlayersSpawned)
				{
					PlayersSpawned++;
					return *StartIt;
				}
			}
		}
	}
	PlayersSpawned++;
	return EmergencyBackup;
}