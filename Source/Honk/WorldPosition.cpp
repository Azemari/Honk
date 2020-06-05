// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values
AWorldPosition::AWorldPosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Position = CreateDefaultSubobject<USceneComponent>(TEXT("Position"));
	RootComponent = Position;
}

// Called when the game starts or when spawned
void AWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldPosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AWorldPosition::GetPosition() 
{
	return Position->GetComponentLocation();
}

FRotator AWorldPosition::GetRotation() 
{
	return Position->GetComponentRotation();
}

