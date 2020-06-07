// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "HonkGameInstance.h"
#include "HonkPawn.h"
#include "HonkMenuHUD.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::Tick(float DeltaTime) 
{
	TArray<AActor*> actors; 
	UGameplayStatics::GetAllActorsOfClass(this, AHonkPawn::StaticClass(), actors);
	for (int i = 0; i < actors.Num(); ++i)
	{
		if (AHonkPawn* cast = Cast<AHonkPawn>(actors[i]))
		{
			HUDWidget->UpdatePlayer(cast->NumLives, cast->health, cast->WeaponName, i);
		}
	}
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnPlayers();
	if (HUD != nullptr)
	{
		HUDWidget = CreateWidget<UGameHudWidget>(UGameplayStatics::GetPlayerController(this, 0), HUD);
		if (HUDWidget != nullptr)
		{	
			TArray<AActor*> actors; 
			UGameplayStatics::GetAllActorsOfClass(this, AHonkPawn::StaticClass(), actors);
			for (int i = 0; i < actors.Num(); ++i)
			{
				if (AHonkPawn* cast = Cast<AHonkPawn>(actors[i]))
				{
					HUDWidget->AddPlayer(cast->NumLives, cast->health, cast->WeaponName, i);
				}
			}
			HUDWidget->AddToViewport();
		}
	}
}

void AGameManager::SpawnPlayers() const
{
	if (UHonkGameInstance* GI = Cast<UHonkGameInstance>(GetGameInstance()))
	{
		for (int i = 0; i < GI->GetNumPlayers(); i++)
		{
			if (UWorld* World = GetWorld())
			{
				APlayerController* PC = UGameplayStatics::CreatePlayer((UObject*)World, i, true);
			}
		}
	}

}

