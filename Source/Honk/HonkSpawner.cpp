// Fill out your copyright notice in the Description page of Project Settings.


#include "HonkSpawner.h"

// Sets default values
AHonkSpawner::AHonkSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHonkSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ArmourTimer, this, &AHonkSpawner::SpawnArmour, ArmourSpawnInterval, true, ArmourInitialSpawnDelay);
	GetWorldTimerManager().SetTimer(WeaponTimer, this, &AHonkSpawner::SpawnWeapon, WeaponSpawnInterval, true, WeaponInitialSpawnDelay);
}

// Called every frame
void AHonkSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHonkSpawner::SpawnArmour() 
{
	UE_LOG(LogTemp, Display, TEXT("Armour Spawned!"));
}

void AHonkSpawner::SpawnWeapon() 
{
	UE_LOG(LogTemp, Display, TEXT("Weapon Spawned!"));
}

