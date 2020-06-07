// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "HonkGameMode.generated.h"

UCLASS()
class AHonkGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	AHonkGameMode();

	virtual void BeginPlay() override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	int PlayersSpawned = 0;

};



