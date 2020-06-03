// Fill out your copyright notice in the Description page of Project Settings.
#include "HonkWeaponDrop.h"

// Sets default values
AHonkWeaponDrop::AHonkWeaponDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropMesh"));
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComp"));
	LightComponent->SetupAttachment(DropMesh);
}

// Called when the game starts or when spawned
void AHonkWeaponDrop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHonkWeaponDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator Rotator = FRotator(0, 180, 0);
	DropMesh->AddWorldRotation(Rotator * speed * DeltaTime);
}

