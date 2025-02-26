// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HonkArmourDrop.h"
#include "HonkWeaponDrop.h"
#include "WorldPosition.h"
#include "TimerManager.h"
#include "Engine/World.h"


#include "HonkSpawner.generated.h"

UCLASS()
class HONK_API AHonkSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHonkSpawner();
	virtual void Tick(float DeltaTime) override;

	void SpawnArmour();
	void SpawnWeapon();

	UPROPERTY(EditAnywhere, Category=ArmourData)
	TSubclassOf<AHonkArmourDrop> ArmourDrop = nullptr;
	UPROPERTY(EditAnywhere, Category=ArmourData)
	TArray<AWorldPosition*> ArmourSpawns;
	UPROPERTY(EditAnywhere, Category=ArmourData)
	float ArmourSpawnInterval = 15;
	UPROPERTY(EditAnywhere, Category=ArmourData)
	int ArmourInitialSpawnDelay = 15;
	FTimerHandle ArmourTimer;

	UPROPERTY(EditAnywhere, Category=WeaponData)
	TSubclassOf<AHonkWeaponDrop> WeaponDrop = nullptr;
	UPROPERTY(EditAnywhere, Category=WeaponData)
	TArray<AWorldPosition*> WeaponSpawns;
	UPROPERTY(EditAnywhere, Category=WeaponData)
	float WeaponSpawnInterval = 15;
	UPROPERTY(EditAnywhere, Category=WeaponData)
	int WeaponInitialSpawnDelay = 15;
	FTimerHandle WeaponTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
